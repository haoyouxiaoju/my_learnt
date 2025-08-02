#include "EPollPoller.hpp"
#include "Channel.hpp"

#include <unistd.h>
#include <stdio.h>


static const int NEW = -1;      /* 新建的Channel 还未添加至Poller */
static const int ADDED = 1;     /* 已添加至Poller */
static const int DELETED = 2;   /* 从Poller 删除*/

EPollPoller::EPollPoller(EventLoop* loop)
    :Poller(loop)
    ,_epoll_fd(::epoll_create1(EPOLL_CLOEXEC))
    ,_events(InitEventListSize){
        if(_epoll_fd < 0){
            LOG_FATAL("epoll create error:%s\n",strerror(errno));
        }
}

EPollPoller::~EPollPoller(){
    if(::close(_epoll_fd) == -1){
        LOG_FATAL("close epoll fd error:%s\n",strerror(errno));
    }
}
/**
 * 进行epoll_wait, 同时输出型参数返回需要处理的channel
 */
TimeStamp EPollPoller::poll(int timeoutMs,ChannelList* activeChannels){
    LOG_DEBUG("func = %s => fd total count:%lu\n",__func__,_channels.size());

    int numEvents = ::epoll_wait(_epoll_fd,_events.data(),static_cast<int>(_events.size()),timeoutMs);
    int saveErrno = errno;
    TimeStamp now(TimeStamp::now());

    if(numEvents > 0){
        LOG_ERROR("%d events happend\n",numEvents);
        fillActiveChannels(numEvents,activeChannels);
        if(numEvents == _events.size()){
            _events.resize(_events.size()*2);
        }
    }else if(numEvents == 0){
        LOG_DEBUG("%s timeout!\n",__func__);
    }else{
        if( errno != EINTR){
            LOG_ERROR("EPollPoller::poll() error:%s!",strerror(errno));
            errno = saveErrno;
        }
    }
    return now;
}

/**
 * 如果channel是NEW或者DELTED
 * 则将channel添加到epoll中管理
 * 如果index是ADDED
 * 那么判断channel是否有事件
 * 没有事件则设置index为DELETED 同时在epoll中也去除,
 * 但不从_channels中删除channel,原因是后续可能需要重新进行监听
 * 如果有事件,那么就对channel在epoll中进行修改
 */
void EPollPoller::updateChannel(Channel* channel){
    const int index = channel->index();
    LOG_DEBUG("func = %s => fd = %d events = %d index = %d\n",__func__,channel->fd(),channel->events(),index);

    if(index == NEW || index == DELETED){
        if(index == NEW){
            int fd = channel->fd();
            _channels[fd] = channel;
        }else{
        }
        channel->set_index(ADDED);
        update(EPOLL_CTL_ADD,channel);
    }else{
        int fd = channel->fd();
        if(channel->isNonEvent()){
            update(EPOLL_CTL_DEL,channel);;
            channel->set_index(DELETED);
        }else{
            update(EPOLL_CTL_MOD,channel);
        }
    }
}
/**
 * 在手动删除channel中才会从_channels中去去除channel
 * 同时去除epoll对此channel的监听
 */
void EPollPoller::removeChannel(Channel* channel){
    int fd = channel->fd();
    _channels.erase(fd);

    LOG_DEBUG("func = %s => fd = %d\n",__func__,fd);

    int index = channel->index();
    if(index == ADDED){
        update(EPOLL_CTL_DEL,channel);
    }
    channel->set_index(NEW);
}

void EPollPoller::fillActiveChannels(int numEvents,ChannelList* avtiveChannels)const{
    for(int i=0;i<numEvents;++i){
        Channel* channel = static_cast<Channel*> (_events[i].data.ptr);
        channel->set_revents(_events[i].events);
        avtiveChannels->push_back(channel);
    }
}
/**
 * 对epoll的 add del mod进行包装
 */
void EPollPoller::update(int operation,Channel* channel){
   epoll_event event;
   ::memset(&event,0,sizeof(event));

   int fd = channel->fd();
   event.events = channel->events();
   event.data.fd = fd;
   event.data.ptr = channel;

   if(::epoll_ctl(_epoll_fd,operation,fd,&event)<0){
    if(operation == EPOLL_CTL_DEL){
        LOG_ERROR("epoll_ctl del error:%s\n",strerror(errno));
    }else{
        LOG_ERROR("epoll_ctl add/mod error:%s\n",strerror(errno));
    }
   }
}
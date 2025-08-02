#include "EventLoop.hpp"
#include "EPollPoller.hpp"
#include "Channel.hpp"

#include <sys/eventfd.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <memory>

thread_local EventLoop* t_loopInThisThread = nullptr;

/** IO 复用接口的超时时间 */
const int PollTimeMs = 1000;

int createEventFd(){
    int event_fd = ::eventfd(0,EFD_NONBLOCK | EFD_CLOEXEC);
    if(event_fd < 0){
        LOG_FATAL("event fd error :%s\n",strerror(errno));
    }
    return event_fd;
}

EventLoop::EventLoop()
    :_looping(false),_quit(false)
    ,_callingPendingFunctors(false)
    ,_thread_id(CurrentThread::tid())
    ,_poller(Poller::newDefaultPoller(this))
    ,_wakeup_fd(createEventFd())
    ,_wakeupChannel(new Channel(this,_wakeup_fd))
{
    LOG_DEBUG("EventLoop created %p in thread %s\n",this,_thread_id);
    if(t_loopInThisThread){
        LOG_FATAL("Another EventLoop %p exists in this thread %d\n",t_loopInThisThread,_thread_id);
        abort();
    }
    else{
        t_loopInThisThread = this;
    }
    _wakeupChannel->setReadCallBack(std::bind(&EventLoop::handleRead,this));

    _wakeupChannel->enableReading();
}
EventLoop::~EventLoop(){
    _wakeupChannel->disableAll();
    _wakeupChannel->remove();
    ::close(_wakeup_fd);
    t_loopInThisThread = nullptr;
}

void EventLoop::loop(){
    _looping = true;
    _quit = false;

    LOG_DEBUG("EventLoop %p start looping \n",this);

    while(!quit){
        _activeChannels.clear();
        _pollReturnTime = _poller->poll(PollTimeMs,&_activeChannels);
        for(Channel* channel : _activeChannels){
            channel->handleEvent(_pollReturnTime);
        }
        doPendingFunctors();
    }
    LOG_DEBUG("EventLoop %p stop looping \n",this);
    _looping = false;
}

void EventLoop::quit(){
    _quit = true;
    if(!isInLoopThread()){
        wakeUp();
    }
}

void EventLoop::runInLoop(Functor cb){
    if(isInLoopThread()){
        cb();
    }else{
        queueInLoop(cb);
    }
}

void EventLoop::queueInLoop(Functor cb){
    {
        std::unique_lock<std::mutex> lock(_mutex);
        _pendingFunctors.emplace_back(cb);
    }
    if(!isInLoopThread() || _callingPendingFunctors){
        wakeUp();
    }
}


void EventLoop::handleRead(){
    uint64_t one = 1;
    ssize_t n = read(_wakeup_fd,&one,sizeof(one));
    if(n != sizeof(one)){
        LOG_ERROR("EventLoop::handleRead() reads %lu bytes instead of 8\n",n);
    }
}

void EventLoop::wakeUp(){
    uint64_t one = 1;
    ssize_t n = write(_wakeup_fd,&one,sizeof(one));
    if(n!= sizeof(one)){
        LOG_ERROR("EventLoop::wakeup() writes %lu bytes instead of 8 \n",n);
    }
}

void EventLoop::updateChannel(Channel* channel){
    _poller->updateChannel(channel);
}
void EventLoop::removeChannel(Channel* channel){
    _poller->removeChannel(channel);
}
bool EventLoop::hasChannel(Channel* channel){
    return _poller->hasChannel(channel);
}

void EventLoop::doPendingFunctors(){
    std::vector<Functor> functors;
    _callingPendingFunctors = true;
    {
        std::unique_lock<std::mutex> lock(_mutex);
        functors.swap(_pendingFunctors);
    }
    for(const Functor& functor:functors){
        functor();
    }
    _callingPendingFunctors = false;
}



#include "Channel.hpp"

#include "EventLoop.hpp"



const int NoneEvent = 0;
const int ReadEvent = EPOLLIN | EPOLLPRI;
const int WriteEvent = EPOLLOUT;

Channel::Channel(EventLoop* loop,int fd)
    :_loop(loop),_fd(fd)
    ,_events(0),_revents(0)
    ,_index(-1),_tied(false){
}

Channel::~Channel(){}

/** Channel绑定TcpConnection 后则_tied去true */
void Channel::tie(const ::std::shared_ptr<void> &obj){
    _tie = obj;
    _tied = true;
}

void Channel::update(){
    _loop->updateChannel(this);
}

void Channel::remove(){
    _loop->removeChannel(this);
}

/** 
 * 判断是否已绑定到TcpConnection中
 * 没有则直接执行
 * 有则 先获取锁判断是否还存活再执行处理函数
 */
void Channel::handleEvent(TimeStamp receiveTime){
    if(_tied){
        std::shared_ptr<void> guard = _tie.lock();
        if(guard){
            handleEventWithGuard(receiveTime);
        }
    }else{
        handleEventWithGuard(receiveTime);
    }
}

/** 根据_revents 具体类型 执行回调函数 */
void Channel::handleEventWithGuard(TimeStamp receiveTime){
    if((_revents & EPOLLHUP) && !(_revents & EPOLLIN)){
        if(_closeCallBack)  
            _closeCallBack();
    }
    if( _revents & EPOLLERR){
        if(_errorCallBack)
            _errorCallBack();
    }
    if( _revents & (EPOLLIN | EPOLLPRI)){
        if(_readCallBack)
            _readCallBack(receiveTime);
    }
    if(_revents & EPOLLOUT){
        if(_writeCallBack)
            _writeCallBack();
    }
}

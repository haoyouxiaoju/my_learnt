#ifndef MUDUO_BASE_CHANNEL_HPP
#define MUDUO_BASE_CHANNEL_HPP

#include "noncopyable.hpp"
#include "Logger.hpp"

#include <memory>
#include <functional>
#include <sys/epoll.h>

class EventLoop;

class Channel : noncopyable{
public:
    using ReadEventCallBack = std::function<void(TimeStamp)>;
    using EventCallBack = std::function<void()>;

    Channel(EventLoop* loop,int fd)
        : _loop(loop),_fd(fd)
        , _events(0),_revents(0)
        , _index(-1),_tied(false) {}
    ~Channel(){}

    void handleEvent(TimeStamp receiveTime);

    /**
     * 防止channel被手动remove后 channel还在执行回调操作
     */
    void tie(const std::shared_ptr<void>&);

    int fd() const      {return _fd;}
    int events() const  {return _events;};
    void set_revents(int revt){ _revents = revt;}
    int index() {return _index;}
    void set_index(int index){ _index = index;}

    EventLoop* ownerLoop(){return _loop;}
    void remove();

    /**
     * 设置fd相应的事件状态 相当于epoll_ctl 的 add delte mov
     */
    void enableReading() { _events |= ReadEvent;    update();}
    void disableReading(){ _events &= ~ReadEvent;   update();}
    void enableWriting() { _events |= WriteEvent;   update();}
    void disableWriting(){ _events &= WriteEvent;   update();}
    void disableAll()    { _events = NoneEvent;     update();}

    /**
     * 返回fd当前的事件状态
     */
    bool isNonEvent() const { return _events == NoneEvent;}
    bool isWriting() const  { return _events & WriteEvent;}
    bool isReading() const  { return _events & ReadEvent ;}

    /**
     * 设置回调函数
     */
    void setReadCallBack(ReadEventCallBack cb)  { _readCallBack  = std::move(cb);}
    void setWriteCallBack(EventCallBack cb)     { _writeCallBack = std::move(cb);} 
    void setCloseCallBack(EventCallBack cb)     { _closeCallBack = std::move(cb);}
    void setErrorCallBack(EventCallBack cb)     { _errorCallBack = std::move(cb);}

private:
    void update();
    void handleEventWithGuard(TimeStamp receiveTime);

private:
    static const int NoneEvent ;    //空事件
    static const int ReadEvent ;    //读事件
    static const int WriteEvent;    //写事件

    /** 事件循环*/
    EventLoop* _loop;
    /**Poller监听的对像*/
    const int _fd;

    /**注册感兴趣的事件*/
    int _events;
    /**Poller返回具体执行的事件*/
    int _revents;
    int _index;

    std::weak_ptr<void> _tie;
    bool _tied;

    /**用于后续回调执行对应事件  */
    ReadEventCallBack _readCallBack;
    EventCallBack _writeCallBack;
    EventCallBack _closeCallBack;
    EventCallBack _errorCallBack;


};




#endif

#ifndef MUDUO_BASE_EVENTLOOP_HPP
#define MUDUO_BASE_EVENTLOOP_HPP

#include "noncopyable.hpp"
#include "TimeStamp.hpp"
#include "CurrentThread.hpp"

#include <functional>
#include <atomic>
#include <unistd.h>
#include <memory>
#include <vector>
#include <mutex>

class Channel;
class Poller;

class EventLoop: noncopyable{
public:
    using Functor = std::function<void()>;

    EventLoop();
    ~EventLoop();

    /** 开启事件循环 */
    void loop();

    void quit();

    TimeStamp pollReturnTime() const { return _pollReturnTime;}
    //在当前loop中执行Functor
    void runInLoop(Functor cb);
    /** 
     * 把上层注册的回调函数cb放入队列中,
     * 唤醒loop所在的线程再执行Functor 
     **/
    void queueInLoop(Functor cb);

    /** 唤醒loop所在的线程 */
    void wakeUp();

    /**
     * 
     */
    void updateChannel(Channel* channel);
    void removeChannel(Channel* channel);
    bool hasChannel(Channel* channel);

    /** 
     * 判断loop对象是否在当前线程中
     **/
    bool isInLoopThread() const{return _thread_id == CurrentThread::tid();}


private:
    using ChannelList = std::vector<Channel*>;

    /**  */
    void handleRead();

    /** 执行上层回调 */
    void doPendingFunctors();

private:
    /** 用于pendingFunctors的线程安全 */
    std::mutex _mutex;
    /** 记录当前loop是由哪个线程创建的 */
    const pid_t _thread_id;

    int _wakeup_fd;
    std::unique_ptr<Channel> _wakeupChannel;

    std::unique_ptr<Poller> _poller;
    TimeStamp _pollReturnTime;

    /** 返回Poller 当前有事件发生的所有Channel列表 */
    ChannelList _activeChannels;

    /** 存储loop需要执行的所有回调操作  */
    std::vector<Functor> _pendingFunctors;
    /** 标识loop是否需要执行回调 */
    std::atomic<bool> _callingPendingFunctors;

    std::atomic<bool> _looping;
    std::atomic<bool> _quit;
};




#endif
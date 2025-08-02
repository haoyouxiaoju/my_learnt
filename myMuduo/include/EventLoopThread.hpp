#ifndef MUDUO_BASE_EVENTLOOPTHREAD_HPP
#define MUDUO_BASE_EVENTLOOPTHREAD_HPP


#include "noncopyable.hpp"
#include "EventLoop.hpp"
#include "Thread.hpp"

#include <functional>
#include <condition_variable>


class EventLoopThread:noncopyable{
public:
    using ThreadInitCallBack  = std::function<void(EventLoop*)>;
    EventLoopThread(const ThreadInitCallBack& cb = ThreadInitCallBack()
        ,const std::string& name = std::string())
        :_loop(nullptr)
        ,_exiting(false)
        ,_thread(std::bind(&EventLoopThread::threadFunc,this),name)
        ,_callback(cb){}
    ~EventLoopThread(){
        _exiting = true;
        if(_loop != nullptr){
            _loop->quit();
            _thread.join();
        }
    }

    EventLoop* startLoop(){
        _thread.start();

        EventLoop* loop = nullptr;
        {
            std::unique_lock<std::mutex> lock(_mutex);
            _cond.wait(lock,[this](){return _loop != nullptr;});
            loop = _loop;
        }
        return loop;
    }

private:
    void threadFunc(){
        EventLoop loop;
        if(_callback){
           _callback(&loop);
        }
        {
            std::unique_lock<std::mutex> lock(_mutex);
            _loop = &loop;
            _cond.notify_one();
        }
        loop.loop();
        std::unique_lock<std::mutex> lock(_mutex);
        _loop = nullptr;
    }

private:
    EventLoop* _loop;
    bool _exiting;
    Thread _thread;
    std::mutex _mutex;
    std::condition_variable _cond;
    ThreadInitCallBack _callback;


};




#endif
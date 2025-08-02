#ifndef MUDUO_BASE_THREAD_HPP
#define MUDUO_BASE_THREAD_HPP

#include "noncopyable.hpp"
#include "CurrentThread.hpp"
#include "Logger.hpp"

#include <thread>
#include <functional>
#include <memory>
#include <string>
#include <atomic>
#include <semaphore.h>


class Thread : noncopyable{
public:
    using ThreadFunc = std::function<void()>;

    explicit Thread(ThreadFunc func, const std::string& name = std::string())
        :_started(false),_joined(false),_func(std::move(func)),_name(name){
            setDefaultName();
        }
    ~Thread(){
        /**
         * 已启动 未join 且线程不为nullptr
         */
        if(_started && !_joined && _thread){
            _thread->detach();
        }
    }

    void start(){
        _started = true;
        sem_t sem;
        sem_init(&sem,false,0);

        _thread = std::make_shared<std::thread>([this,&sem](){
            _tid = CurrentThread::tid();
            sem_post(&sem);
            _func();
        });

        /**
         * 这里进行了信号量的等待
         * 所以不需要考虑_thread中信号量是否还存在
         */
        sem_wait(&sem);
        sem_destroy(&sem);
    }
    void join(){
        /**
         * 未启动 或者 已join 直接返回
         */
        if(!_started || _joined){
            LOG_ERROR("the %s is started yeid or joined",name());
            return ;
        }
        if(_thread && _thread->joinable()){
            _joined = true;
            _thread->join();
        }
    }

    bool started(){return _started;}
    pid_t t_id() const { 
        if(!_started){
            LOG_ERROR("the thread is started yeid");
        }
        return _tid;
    }
    const std::string& name() const { return _name;}

    static int numCreated(){return _numCreated;}


private:
    void setDefaultName(){
        int num = ++_numCreated;
        if(_name.empty()){
            char buff[64] ;
            snprintf(buff,sizeof(buff),"Thread-%d",num);
            _name = buff;
        }
    }

    bool _started;
    bool _joined;
    std::shared_ptr<std::thread> _thread;
    pid_t _tid;
    ThreadFunc _func;

    std::string _name;
    static std::atomic<int> _numCreated;

};



#endif
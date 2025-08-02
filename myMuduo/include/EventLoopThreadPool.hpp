#ifndef MUDUO_BASE_EVENTLOOPTHREADPOOL_HPP
#define MUDUO_BASE_EVENTLOOPTHREADPOOL_HPP

#include "noncopyable.hpp"
#include "EventLoopThread.hpp"

#include <functional>




class EventLoopThreadPool : noncopyable{
public:
    using ThreadInitCallBack = std::function<void(EventLoop*)>;
    EventLoopThreadPool(EventLoop* baseLoop,const std::string& name)
        :_baseLoop(baseLoop),_name(name),_started(false)
        ,_numThread(0),_next(0){}
    ~EventLoopThreadPool(){}

    void setThreadNum(int numThread){
        _numThread = numThread;
    }
    
    void start(const ThreadInitCallBack& cb = ThreadInitCallBack()){
        _started = true;
        for(int i = 0 ; i < _numThread ; ++i){
            char buff[_name.size() + 32];
            snprintf(buff,sizeof(buff),"%s%d",_name.c_str(),i);
            EventLoopThread* t = new EventLoopThread(cb,buff);
            _threads.push_back(std::unique_ptr<EventLoopThread>(t));
            _loops.push_back(t->startLoop());
        }
        if( _numThread == 0 && cb){
            cb(_baseLoop);
        }
    }

    EventLoop* getNextLoop(){
        EventLoop* loop = _baseLoop;
        if(!_loops.empty()){
            loop = _loops[++_next];
            if(_next >= _loops.size()){
                _next = 0;
            }
        }
        return loop;
    }
    
    std::vector<EventLoop*> getAllLoops(){
        if(!_loops.empty()){
            return _loops;
        }else{
            return std::vector<EventLoop*>(1,_baseLoop);
        }
    }
    
    bool started() const{return _started;}
    const std::string name() const {return _name;}



private:
    EventLoop* _baseLoop;
    std::string _name;
    bool _started;
    int _numThread;
    int _next;
    std::vector<std::unique_ptr<EventLoopThread>> _threads;
    std::vector<EventLoop*> _loops;

};




#endif
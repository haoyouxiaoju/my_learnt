#include "Poller.hpp"
#include "EPollPoller.hpp"

#include <stdlib.h>


Poller* Poller::newDefaultPoller(EventLoop* loop){
    char* path = ::getenv("MUDUO_USE_POLLER");
    if(path){
        return nullptr;
    }else{
        return new EPollPoller(loop);
    }
}
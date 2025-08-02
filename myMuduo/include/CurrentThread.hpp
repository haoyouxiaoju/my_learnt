#ifndef MUDUO_BASE_CURRENT_THREAD_HPP
#define MUDUO_BASE_CURRENT_THREAD_HPP

#include <unistd.h>
#include <sys/syscall.h>


namespace CurrentThread{
    
thread_local int _t_cache_id = 0;

inline int tid(){
    if(__builtin_expect(_t_cache_id == 0,0)){
        _t_cache_id = static_cast<pid_t>(::syscall(SYS_gettid));
    }
    return _t_cache_id;
}

}




#endif
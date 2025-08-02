#ifndef TIME_STAMP_H
#define TIME_STAMP_H

#include <iostream>
#include <string>
#include <time.h>
#include <string.h>


class TimeStamp{
public:
    TimeStamp(){}
    ~TimeStamp(){}
    explicit TimeStamp(int64_t microSecondsSinceEpoch)
     :_microSecondsSinceEpoch(microSecondsSinceEpoch){}
    static TimeStamp now(){
        return TimeStamp(::time(NULL));
    }
    std::string toString() const{
        char buff[128];
        ::memset(buff,0,sizeof(char)*sizeof(buff));
        tm* tm_time = ::localtime(&_microSecondsSinceEpoch);
        snprintf(buff,128,"%4d/%02d/%02d %02d:%02d:%02d",
          tm_time->tm_year + 1900,
          tm_time->tm_mon + 1,
          tm_time->tm_mday,
          tm_time->tm_hour,
          tm_time->tm_min,
          tm_time->tm_sec  
        );
        return buff;
    }
private:
    int64_t _microSecondsSinceEpoch;

};



#endif
#ifndef MUDUO_BASE_LOGGER_HPP
#define MUDUO_BASE_LOGGER_HPP

#include "noncopyable.hpp"
#include "TimeStamp.hpp"
#include <string>

//日志等级
enum LogLevel{
    INFO,
    ERROR,
    FATAL,
    DEBUG
};

class Logger : noncopyable{
public:
    //获取Logger单例
    static Logger& getInstance(){
        static Logger instance;
        return instance;

    }
    void log(std::string msg,LogLevel level = ERROR){
        std::string level_str;
        switch(level){
            case INFO:
                level_str = "[INFO] ";
                break;
            case ERROR:
                level_str = "[ERROR] ";
                break;
            case FATAL:
                level_str = "[FATAL] ";
                break;
            case DEBUG:
                level_str = "[DEBUG] ";
                break;
            default:
                level_str = "[ERROR] ";
                break;
        }
        // 打印时间和msg
        std::cout << level_str + TimeStamp::now().toString()<< " " << msg << std::endl;
    }
};

#define LOG(logmsgFormat, logLevel, ...)                                  \
    do                                                                    \
    {                                                                     \
        Logger &logger = Logger::getInstance();                           \
        char buf[1024] = {0};                                             \
        char msg[1024] = {0};                                             \
        snprintf(msg, sizeof(msg), logmsgFormat, ##__VA_ARGS__);          \
        snprintf(buf, sizeof(buf), "%s-%d: %s\n", __FILE__, __LINE__, msg); \
        logger.log(buf, logLevel);                                        \
    } while (0)
#define LOG_INFO(logmsgFormat,...)  LOG(logmsgFormat,INFO,   ##__VA_ARGS__) 
#define LOG_DEBUG(logmsgFormat,...) LOG(logmsgFormat,DEBUG, ##__VA_ARGS__)
#define LOG_ERROR(logmsgFormat,...) LOG(logmsgFormat,ERROR, ##__VA_ARGS__)
#define LOG_FATAL(logmsgFormat,...)                                      \
    do{                                                                  \
        LOG(logmsgFormat,FATAL, ##__VA_ARGS__);                          \ 
        exit(-1);                                                          \      
    }while(0)                                                               


// [INFO] 2025/07/20 22:08:13  test.cc-11: info
// [DEBUG] 2025/07/20 22:08:13  test.cc-12: debug
// [FATAL] 2025/07/20 22:08:13  test.cc-13: fatal
// [ERROR] 2025/07/20 22:08:13  test.cc-14: error


#endif
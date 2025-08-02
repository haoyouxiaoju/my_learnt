#ifndef MUDUO_BASE_CALLBACKFUNCTION_HPP
#define MUDUO_BASE_CALLBACKFUNCTION_HPP


#include <functional>
#include <memory>

class TcpConnection;
class TimeStamp;
class Buffer;


using TcpConnectionPtr = std::shared_ptr<TcpConnection>;
using ConnectionCallback = std::function<void(const TcpConnectionPtr &)>;
using CloseCallback = std::function<void(const TcpConnectionPtr &)>;
using WriteCompleteCallback = std::function<void(const TcpConnectionPtr &)>;
using HighWaterMarkCallback = std::function<void(const TcpConnectionPtr &, size_t)>;

using MessageCallback = std::function<void(const TcpConnectionPtr &,
                                           Buffer *,
                                           TimeStamp)>;


#endif
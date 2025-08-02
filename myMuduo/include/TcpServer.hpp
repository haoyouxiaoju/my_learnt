#ifndef MUDUO_BASE_TCPSERVER_HPP
#define MUDUO_BASE_TCPSERVER_HPP


#include "EventLoopThreadPool.hpp"
#include "CallbackFunction.hpp"

#include <unordered_map>

class Acceptor;
class InetAddress;


class TcpServer{
public:
    using ThreadInitCallback = std::function<void (EventLoop*)>;
    enum Option{
        NonReusePort,
        ReusePort
    };
    TcpServer(EventLoop* loop,
              const InetAddress& listenAddr,
              const std::string& name,
              Option option = NonReusePort);
    ~TcpServer();

    void setThreadInitCallback(const ThreadInitCallback& cb);
    void setConnectionCallback(const ConnectionCallback& cb);
    void setMessageCallback(const MessageCallback& cb);
    void setWriteCompleteCallback(const WriteCompleteCallback& cb);

    void setThreadNum(int numThread);


    void start();
private:
    using ConnectionMap = std::unordered_map<std::string,TcpConnectionPtr>;

    void newConnection(int sockfd,const InetAddress& peerAddr);
    void removeConnection(const TcpConnectionPtr& conn);
    void removeConnectionInLoop(const TcpConnectionPtr& conn);

private:
    EventLoop* _loop;

    const std::string _ipPort;
    const std::string _name;

    std::unique_ptr<Acceptor> _acceptor;
    std::shared_ptr<EventLoopThreadPool> _threadPool;

    ConnectionCallback _connectionCallback;
    MessageCallback _messageCallback;
    WriteCompleteCallback _writeCompleteCallback;

    ThreadInitCallback _threadInitCallback;

    int _numThread;
    std::atomic<int> _started;
    int _nextConnId;
    ConnectionMap _connections;

};



#endif
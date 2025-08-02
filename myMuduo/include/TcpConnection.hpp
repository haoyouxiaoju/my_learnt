#ifndef  MUDUO_BASE_TCPCONNECTION_HPP
#define  MUDUO_BASE_TCPCONNECTION_HPP


#include "noncopyable.hpp"
#include "InetAddress.hpp"
#include "CallbackFunction.hpp"
#include "Buffer.hpp"

#include <iostream>
#include <atomic>



class EventLoop;
class Socket;
class Channel;


class TcpConnection : noncopyable ,public std::enable_shared_from_this<TcpConnection>{
public:
    TcpConnection(EventLoop* loop,
                  const std::string& name,
                  int sockfd,
                  const InetAddress& localAddr,
                  const InetAddress& peerAddr);
    ~TcpConnection();

    
    
    void send(const std::string& buff);
    void sendFile(int fileDescriptor,off_t offset,size_t count);
    
    void shutdown();

    void connectEstablished();
    void connectDestroyed();
    
    EventLoop* getLoop()const {return _loop;}
    const std::string& name() const{return _name;}
    const InetAddress& localAddress() const{return _localAddr;}
    const InetAddress& peerAddress() const{return _peerAddr;}
    bool connected() const {return _state == Connected;}
    void setConnectionCallback(const ConnectionCallback& cb){_connectionCallback = cb;}
    void setMessageCallback(const MessageCallback& cb){_messageCallback = cb;}
    void setWriteCompleteCallback(const WriteCompleteCallback& cb){_writeCompleteCallback = cb;}
    void setCloseCallback(const CloseCallback& cb){_closeCallback = cb;}
    void setHighWaterMarkCallback(const HighWaterMarkCallback& cb,size_t highWaterMark){_highWaterMark = highWaterMark;_highWaterMarkCallback=cb;}



private:
    enum State{
        Connecting,     //正在连接
        Connected,      //已连接
        Disconnecting,  //正在断开
        Disconnected    //已断开
    };

    void setState(State state){_state = state;}

    void handleRead(TimeStamp receiveTime);
    void handleWrite();
    void handleClose();
    void handleError();

    void sendInLoop(const void* data,size_t len);
    void shutdownInLoop();
    void sendFileInLoop(int fileDescriptor,off_t offset,size_t count);

private:
    EventLoop* _loop;
    const std::string _name;
    std::atomic<State> _state;
    bool _reading;

    std::unique_ptr<Socket> _socket;
    std::unique_ptr<Channel> _channel;

    const InetAddress _localAddr;
    const InetAddress _peerAddr;

    ConnectionCallback _connectionCallback;
    MessageCallback _messageCallback;
    WriteCompleteCallback _writeCompleteCallback;
    HighWaterMarkCallback _highWaterMarkCallback;
    CloseCallback _closeCallback;
    size_t _highWaterMark;

    Buffer _inputBuffer;
    Buffer _outputBuffer;


};





#endif
#ifndef MUDUO_BASE_ACCEPTER_HPP
#define MUDUO_BASE_ACCEPTER_HPP

#include "noncopyable.hpp"
#include "EventLoop.hpp"
#include "Channel.hpp"
#include "Socket.hpp"

class Acceptor: noncopyable{
public:
    using NewConnectionCallBack = std::function<void(int ,const InetAddress&)>;

    Acceptor(EventLoop* loop,const InetAddress& listenAddr,bool reuseport)
        :_acceptSocket(createNonblocking())
        ,_acceptChannel(_loop,_acceptSocket.fd())
        ,_listenning(false){
            _acceptSocket.setReuseAddr(true);
            _acceptSocket.setReusePort(true);
            _acceptSocket.bindAddress(listenAddr);
            _acceptChannel.setReadCallBack(std::bind(&Acceptor::handleRead,this));
        }
    ~Acceptor(){
        _acceptChannel.disableAll();
        _acceptChannel.remove();
    }
    /** 设置连接回调函数 */
    void setNewConnectionCallBack(const NewConnectionCallBack& cb){_newConnectionCallBack = cb;}

    /** 判断是否在监听 */
    bool listenning() const { return _listenning ;}
    /** 监听本地端口 */
    void listen(){
        _listenning = true;
       _acceptSocket.listen();
       _acceptChannel.enableReading();
    }
private:
    /** 创建非阻塞端口 */
    static int createNonblocking(){
        int sockfd = ::socket(AF_INET,SOCK_STREAM | SOCK_NONBLOCK , IPPROTO_TCP);
        if(sockfd < 0){
            LOG_FATAL("listen socket create err:%s\n",strerror(errno));
        }
        return sockfd;
    }
    /** 处理新用户连接事件  */
    void handleRead(){
         InetAddress peerAddr;
        int connfd = _acceptSocket.accept(&peerAddr);
        if(connfd >= 0){
            if(_newConnectionCallBack){
                _newConnectionCallBack(connfd,peerAddr);
            }else{                
                ::close(connfd);
                LOG_FATAL("accept error : newConnectionCallBack is nullptr");
            }
        }else{
            LOG_ERROR("accept error :%s",strerror(errno));
            if(errno == EMFILE){
                LOG_ERROR("sockfd reached limit");
            }
        }
    }

private:
    EventLoop* _loop;
    /** 监听端口 */
    Socket _acceptSocket;   
    /** 监听通道 */
    Channel _acceptChannel;
    NewConnectionCallBack _newConnectionCallBack;
    bool _listenning;
};



#endif
#ifndef MUDUO_BASE_SOCKET_HPP
#define MUDUO_BASE_SOCKET_HPP

#include "noncopyable.hpp"
#include "InetAddress.hpp"
#include "Logger.hpp"
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/tcp.h>


/**
 * 封装 socket fd
 */
class Socket : noncopyable{
public:
    explicit Socket(int sockfd)
        :_sockfd(sockfd){}
    ~Socket(){
        ::close(_sockfd);
    }

    int fd() const {return _sockfd;}
    void bindAddress(const InetAddress &addr){
        if(0 != ::bind(_sockfd,(sockaddr*)addr.getSockAddr(),sizeof(sockaddr_in))){
            LOG_ERROR("bind socket fd: %d is fail\n",_sockfd);
        }
    }
    void listen(int n = 1024){
        if(0 != ::listen(_sockfd,n)){
            LOG_ERROR("listen socket fd: %d is fail\n",_sockfd);
        }
    }
    /**
     * 非阻塞
     */
    int accept(InetAddress* peeraddr){
        sockaddr_in addr;
        socklen_t len = sizeof(addr);
        ::memset(&addr,0,sizeof(addr));
        int fd = ::accept4(_sockfd,(sockaddr*)&addr,&len,SOCK_NONBLOCK | SOCK_CLOEXEC);
        if(fd >= 0){
            peeraddr->setSockAddr(addr);
        }
        return fd;
    }

    void shutdownWrite(){
        if(::shutdown(_sockfd,SHUT_WR) < 0){
            LOG_ERROR("%d shutdownWrite is fail",_sockfd);
        }
    }

    void setTcpNoDelay(bool on){
        // TCP_NODELAY 用于禁用 Nagle 算法。
        // Nagle 算法用于减少网络上传输的小数据包数量。
        // 将 TCP_NODELAY 设置为 1 可以禁用该算法，允许小数据包立即发送。
        int optval = on ? 1 : 0;
        ::setsockopt(_sockfd, IPPROTO_TCP, TCP_NODELAY, &optval, sizeof(optval));
    }
    void setReuseAddr(bool on)
    {
        // SO_REUSEADDR 允许一个套接字强制绑定到一个已被其他套接字使用的端口。
        // 这对于需要重启并绑定到相同端口的服务器应用程序非常有用。
        int optval = on ? 1 : 0;
        ::setsockopt(_sockfd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));
    }
    void setReusePort(bool on)
    {
        // SO_REUSEPORT 允许同一主机上的多个套接字绑定到相同的端口号。
        // 这对于在多个线程或进程之间负载均衡传入连接非常有用。
        int optval = on ? 1 : 0;
        ::setsockopt(_sockfd, SOL_SOCKET, SO_REUSEPORT, &optval, sizeof(optval));
    }
    void setKeepAlive(bool on)
    {
        // SO_KEEPALIVE 启用在已连接的套接字上定期传输消息。
        // 如果另一端没有响应，则认为连接已断开并关闭。
        // 这对于检测网络中失效的对等方非常有用。
        int optval = on ? 1 : 0;
        ::setsockopt(_sockfd, SOL_SOCKET, SO_KEEPALIVE, &optval, sizeof(optval));
    }

private:
    const int _sockfd;


};



#endif
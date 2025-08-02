#ifndef MUDUO_BASE_INETADDRESS_HPP
#define MUDUO_BASE_INETADDRESS_HPP

#include <netinet/in.h>
#include <string>
#include <string.h>
#include <arpa/inet.h>

/**
 * 封装 sockaddr_in
 */
class InetAddress{
public:
    explicit InetAddress(uint16_t port=0,std::string ip="127.0.0.1"){
        ::memset(&_addr,0,sizeof(_addr));
        _addr.sin_family = AF_INET;
        _addr.sin_port =  ::htons(port);
        _addr.sin_addr.s_addr = ::inet_addr(ip.c_str());
    }
    explicit InetAddress(const sockaddr_in& addr):_addr(addr){}

    std::string toIp() const{
        char buff[64];
        ::memset(buff,0,sizeof(buff));
        ::inet_ntop(AF_INET,&_addr.sin_addr,buff,sizeof(buff));
        return buff;
    }
    uint16_t toPort() const{
        return ::ntohs(_addr.sin_port);
    }
    std::string toIpPort() const{
        return toIp()+":"+std::to_string(toPort());
    }

    const sockaddr_in* getSockAddr() const{return &_addr;}
    void setSockAddr(const sockaddr_in& addr){_addr = addr;}

private:
    sockaddr_in _addr;


};

// /* Internet address.  */
// typedef uint32_t in_addr_t;
// struct in_addr
//   {
//      in_addr_t s_addr;
//   };
// 

// /* Structure describing an Internet socket address.  */
// struct sockaddr_in
//   {
//     __SOCKADDR_COMMON (sin_);
//     in_port_t sin_port;                 /* Port number.  */
//     struct in_addr sin_addr;            /* Internet address.  */
//     /* Pad to size of `struct sockaddr'.  */
//     unsigned char sin_zero[sizeof (struct sockaddr)
//                            - __SOCKADDR_COMMON_SIZE
//                            - sizeof (in_port_t)
//                            - sizeof (struct in_addr)];
//   };


#endif
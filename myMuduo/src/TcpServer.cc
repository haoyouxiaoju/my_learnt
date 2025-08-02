#include "TcpServer.hpp"
#include "TcpConnection.hpp"
#include "Accepter.hpp"


static EventLoop* CheckLoopNotNull(EventLoop* loop){
    if(loop == nullptr){
        LOG_FATAL("main loop is null");
    }
    return loop;
}

TcpServer::TcpServer(EventLoop* loop
                    ,const InetAddress& listenAddr
                    ,const std::string& name
                    ,Option option)
    :_loop(CheckLoopNotNull(loop))
    ,_ipPort(listenAddr.toIpPort())
    ,_name(name)
    ,_acceptor(new Acceptor(_loop,listenAddr,option == ReusePort))
    ,_threadPool(new EventLoopThreadPool(_loop,_name))
    ,_connectionCallback()
    ,_messageCallback()
    ,_nextConnId(1)
    ,_started(0){
        _acceptor->setNewConnectionCallBack(
            std::bind(&TcpServer::newConnection,this,std::placeholders::_1,std::placeholders::_2)
        );
    }

TcpServer::~TcpServer(){
    for(auto &item:_connections){
        TcpConnectionPtr conn(item.second);
        item.second.reset();
        conn->getLoop()->runInLoop(
            std::bind(&TcpConnection::connectDestroyed,conn)
        );
    }
}

void TcpServer::setThreadNum(int num){
    _threadPool->setThreadNum(num);
}

void TcpServer::start(){
    if(_started.fetch_add(1) == 0){
        _threadPool->start(_threadInitCallback);
        _loop->runInLoop(std::bind(&Acceptor::listen,_acceptor.get()));
    }
}

void TcpServer::newConnection(int sockfd,const InetAddress& peerAddr){
    EventLoop* ioLoop = _threadPool->getNextLoop();
    char buff[64] = {0};
    snprintf(buff,sizeof (buff),"-%s#%d",_ipPort.c_str(),_nextConnId);
    ++_nextConnId;
    std::string connName = _name + buff;
    LOG_INFO("TcpServer::newConnection [%s] - new connection [%s] from %s\n",_name.c_str(),connName.c_str());

    sockaddr_in local;
    socklen_t addrlen = sizeof(local);
    ::memset(&local,0,addrlen);
    if(::getsockname(sockfd,(sockaddr*)&local,&addrlen)< 0){
        LOG_ERROR("sockets::getLocalAddr");
    }
    InetAddress localAddr(local);
    TcpConnectionPtr conn(
        new TcpConnection(ioLoop
                         ,connName
                         ,sockfd
                         ,localAddr
                         ,peerAddr));
    _connections[connName] == conn;
    conn->setConnectionCallback(_connectionCallback);
    conn->setMessageCallback(_messageCallback);
    conn->setWriteCompleteCallback(_writeCompleteCallback);

    conn->setCloseCallback(std::bind(&TcpServer::removeConnection,this,std::placeholders::_1));
    ioLoop->runInLoop(std::bind(&TcpConnection::connectEstablished,conn));
}

void TcpServer::removeConnection(const TcpConnectionPtr& conn){
    _loop->runInLoop(std::bind(&TcpServer::removeConnectionInLoop,this,conn));
}

void TcpServer::removeConnectionInLoop(const TcpConnectionPtr& conn){
    LOG_INFO("TcpServer::removeConnectionInLoop [%s] - connection %s",_name.c_str(),conn->name().c_str());

    _connections.erase(conn->name());
    EventLoop* ioLoop = conn->getLoop();
    ioLoop->queueInLoop(std::bind(&TcpConnection::connectDestroyed,conn));
}


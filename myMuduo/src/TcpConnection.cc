#include "TcpConnection.hpp"

#include "Logger.hpp"
#include "Socket.hpp"
#include "Channel.hpp"
#include "EventLoop.hpp"

#include <sys/sendfile.h>


static constexpr int HIGHWATERMARK = 64*1024*1024;

static EventLoop* checkLoopNotNull(EventLoop* loop){
    if(loop == nullptr){
        LOG_FATAL("mainLoop is null!\n");
    }
    return loop;
}


TcpConnection::TcpConnection(
     EventLoop* loop
    ,const std::string& name
    ,int sockfd
    ,const InetAddress& localAddress
    ,const InetAddress& peerAddress)
        :_loop(checkLoopNotNull(loop))
        ,_name(name)
        ,_state(Connecting)
        ,_reading(true)
        ,_socket(new Socket(sockfd))
        ,_channel(new Channel(loop,sockfd))
        ,_localAddr(localAddress)
        ,_peerAddr(peerAddress)
        ,_highWaterMark(HIGHWATERMARK){

    _channel->setReadCallBack(std::bind(&TcpConnection::handleRead,this,std::placeholders::_1));
    _channel->setWriteCallBack(std::bind(&TcpConnection::handleWrite,this));
    _channel->setCloseCallBack(std::bind(&TcpConnection::handleClose,this));
    _channel->setErrorCallBack(std::bind(&TcpConnection::handleError,this));

    LOG_INFO("Tcpconnection::ctor[%s] at fd=%d",_name.c_str(),sockfd);
    _socket->setKeepAlive(true);

}

TcpConnection::~TcpConnection(){
    LOG_INFO("Tcpconnection::dtor[%s] at fd=%d state=%d",_name.c_str(),_channel->fd(),(int)_state);
}

void TcpConnection::send(const std::string& buff){
    if(_state == Connected){
        if( _loop->isInLoopThread()){
            sendInLoop(buff.c_str(),buff.size());
        }else{
            _loop->runInLoop(std::bind(&TcpConnection::sendInLoop,this,buff.c_str(),buff.size()));
        }
    }
}

void TcpConnection::sendInLoop(const void* data,size_t len){
    ssize_t nwrote = 0;
    size_t remaining = len;
    bool faultError = false;

    if( _state == Disconnected){
        LOG_ERROR("disconnected give up writing");
    }
    if(!_channel->isWriting() && _outputBuffer.readableBytes() == 0){
        nwrote = ::write(_channel->fd(),data,len);
        if(nwrote>=0){
            remaining = len - nwrote;
            if(remaining == 0 && _writeCompleteCallback){
                _loop->queueInLoop(std::bind(_writeCompleteCallback,shared_from_this()));
            }
        }else{
            nwrote = 0;
            if(errno != EWOULDBLOCK){
                LOG_ERROR("Tcpconnection::sendInLoop");
                if(errno == EPIPE || errno == ECONNRESET){
                    faultError = true;
                }
            }
        }
    }
    if (!faultError && remaining > 0)
    {
        size_t oldLen = _outputBuffer.readableBytes();
        if (oldLen + remaining >= _highWaterMark && oldLen < _highWaterMark && _highWaterMarkCallback)
        {
            _loop->queueInLoop(std::bind(_highWaterMarkCallback, shared_from_this(), oldLen + remaining));
        }
        _outputBuffer.append((char *)data + nwrote, remaining);
        if (!_channel->isWriting())
        {
            _channel->enableWriting();
        }
    }
}

void TcpConnection::shutdown(){
    if(_state == Connected){
        setState(Disconnected);
        _loop->runInLoop(std::bind(&TcpConnection::shutdownInLoop,this));
    }
}

void TcpConnection::shutdownInLoop(){
    if(!_channel->isWriting()){
        _socket->shutdownWrite();
    }
}

void TcpConnection::connectEstablished(){
    setState(Connected);
    _channel->tie(shared_from_this());
    _channel->enableReading();

    _connectionCallback(shared_from_this());
}

void TcpConnection::connectDestroyed(){
    if(_state == Connected){
        setState(Disconnected);
        _channel->disableAll();
        _connectionCallback(shared_from_this());
    }
    _channel->remove();
}

void TcpConnection::handleRead(TimeStamp receiveTime){
    int saveErrno = 0;
    ssize_t n = _inputBuffer.readFd(_channel->fd(),&saveErrno);
    if(n>0){
        _messageCallback(shared_from_this(),&_inputBuffer,receiveTime);
    }else if(n == 0){
        handleClose();
    }else{
        errno = saveErrno;
        LOG_ERROR("TcpConnection::handleRead");
        handleError();
    }
}

void TcpConnection::handleWrite(){
    if(_channel->isWriting()){
        int saveErrno = 0; 
        ssize_t n= _outputBuffer.writeFd(_channel->fd(),&saveErrno);
        if(n>0){
            _outputBuffer.retrieve(n);
            if(_outputBuffer.readableBytes() == 0){
                _channel->disableWriting();
                if(_writeCompleteCallback){
                    _loop->queueInLoop(std::bind(_writeCompleteCallback,shared_from_this()));
                }
                if(_state == Disconnecting){
                    shutdownInLoop();
                }
            }else{
                LOG_ERROR("TcpConnection::handleWrite");
            }
        }else{
            LOG_ERROR("TcpConnection fd=%d is down,no more writing",_channel->fd());
        }
    }
}


void TcpConnection::handleClose(){
    LOG_INFO("TcpConnection::handleClose fd = %d state = %d\n",_channel->fd(),(int)_state);
    setState(Disconnected);
    _channel->disableAll();
    TcpConnectionPtr connPtr(shared_from_this());
    ConnectionCallback(connPtr);
    _closeCallback(connPtr);
}

void TcpConnection::handleError(){
    int optval;
    socklen_t optlen = sizeof optval;
    int err = 0;
    if(::getsockopt(_channel->fd(),SOL_SOCKET,SO_ERROR,&optval,&optlen) < 0){
        err = errno;
    }else{
        err = optval;
    }
    LOG_ERROR("TcpConnection::handleError name:%s - SO_ERROR:%d\n",_name.c_str(),err);
}

void TcpConnection::sendFile(int fileDescriptor,off_t offset,size_t count){
    if(connected()){
        if(_loop->isInLoopThread()){
            sendFileInLoop(fileDescriptor,offset,count);
        }else{
            _loop->runInLoop(std::bind(&TcpConnection::sendFileInLoop
                    ,shared_from_this(),fileDescriptor,offset,count));
        }
    }else{
        LOG_ERROR("TcpConnection::sendFIle - not connected");
    }
}

void TcpConnection::sendFileInLoop(int fileDescriptor,off_t offset,size_t count){
    ssize_t bytesSent = 0;
    size_t remaining = count;
    bool faultError = false;

    if(_state == Disconnecting){
        LOG_ERROR("disconnected , give up writing");
        return ;
    }
    if(!_channel->isWriting() && _outputBuffer.readableBytes()){
        bytesSent = sendfile(_socket->fd(),fileDescriptor,&offset,remaining);
        if(bytesSent >= 0){
            remaining -= bytesSent;
            if(remaining == 0 && _writeCompleteCallback){
                _loop->queueInLoop(std::bind(_writeCompleteCallback,shared_from_this()));
            }
        }else{
            if(errno != EWOULDBLOCK){
                LOG_ERROR("TcpConnection::sendFileInLoop");
            }
            if(errno == EPIPE || errno == ECONNRESET){
                faultError = true;
            }
        }
    }
    if(!faultError && remaining > 0){
        _loop->queueInLoop(std::bind(&TcpConnection::sendFileInLoop,shared_from_this(),fileDescriptor,offset,remaining));
    }


}
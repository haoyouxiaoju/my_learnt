#include "Buffer.hpp"
#include <string.h>
#include <sys/uio.h>
#include <errno.h>
#include <unistd.h>


/*
*   initalSize - 指定Buffer的存储大小
*   默认值为 INITIALSIZE 1024
*/
Buffer::Buffer(size_t initalSize)
    : _data(initalSize + CHEAPPREPEND)
    , _readerIndex(CHEAPPREPEND)
    , _writerIndex(CHEAPPREPEND){}

/**
 * len < 可读数据字节大小则只读len大小数据
 * else 则全部读取,将index设置为起始位置
 */
void Buffer::retrieve(size_t len){
    if(len < readableBytes()){
        _readerIndex += len;
    }else{
        retrieveAll();
    }
}
/**
 * 全部读取,将index设置为起始位置
 */
void Buffer::retrieveAll(){
    _readerIndex = CHEAPPREPEND;
    _writerIndex = CHEAPPREPEND;
}

/**
 * 读取缓冲区内数据
 */
std::string Buffer::retrieveAsString(size_t len){
    std::string result(begin(),len);
    retrieve(len);
    return result;
}
std::string Buffer::retrieveAllAsString(){
    return retrieveAsString(readableBytes());
}

/* 将长度为 len 的 数据 写入缓存区 尾部 */
void Buffer::append(const char* data,size_t len){
    // 先确保有充足空间写入数据
    ensureWritableBytes(len);
    std::copy(data,data+len,beginWrite());
    _writerIndex += len;
}

/**从 文件 中读取数据 写入缓冲区
 * 由于不确定具体文件读取数据大小
 * 使用readv来读取数据
*/
ssize_t Buffer::readFd(int fd, int *saveError)
{
    char extrabuff[65536];
    // struct iovec
    // {
    //     void *iov_base;          /* BSD uses caddr_t (1003.1g requires void *) */
    //     __kernel_size_t iov_len; /* Must be size_t (1003.1g) */
    // };
    struct iovec vec[2];
    size_t writableLen = writableBytes();
    vec[0].iov_base = beginWrite();
    vec[0].iov_len = writableLen;

    vec[1].iov_base = extrabuff;
    vec[1].iov_len = sizeof(extrabuff);

    // 如果缓冲区内可写入区域本身就比较大,则考虑不使用扩展的栈空间了
    const int iovcnt = (writableLen > sizeof(extrabuff))? 1 : 2 ;
    ssize_t n = ::readv(fd,vec,iovcnt);

    if(n < 0 ){
        *saveError = errno;         //读取失败
    }
    else if(n < writableLen){
        _writerIndex + n;           //更新前面readv写入_data后的下标
    }
    else{
        _writerIndex = _data.size(); //更新前面readv写入_data后的下标
        append(extrabuff,n - writableLen);
    }

    return n;
}
/* 将缓冲区数据写入 文件 中*/
ssize_t Buffer::writeFd(int fd, int *saveError)
{
    ssize_t n = ::write(fd,peek(),readableBytes());
    if(n < 0){
        *saveError = errno;     //写入失败
    }
    return n;
}

/**
 * private
 * private
 * private
 */


/* 返回_data底层数组的首地址 */
char* Buffer::begin(){
    return _data.data();
}

const char* Buffer::begin() const{
    return _data.data();
}

/* 返回缓冲区可写入的数据的地址 */
char *Buffer::beginWrite()
{
    return begin()+_writerIndex;
}

const char *Buffer::beginWrite() const
{
    return begin()+_writerIndex;
}

/* 确保len字节的空间可写入数据,空间不够则扩容 */
void Buffer::ensureWritableBytes(size_t len){
    if(len > writableBytes()){
        makeSpace(len);
    }
}

/* 缓冲区可读数据的起始位置 */
const char *Buffer::peek() const
{
    return begin() + _readerIndex;
}

/* 重新整合缓冲区数据的分布
 * 1. len + cheapprepend < prependableBytes() + writerableBytes()
 *    则考虑将缓冲区未读数据向前拷贝覆盖掉已读区域,增加可写入区域大小
 * 2. else
 *    则考虑直接vector.resize()
 */
void Buffer::makeSpace(size_t len){
    if(len + CHEAPPREPEND > prependableBytes() + writableBytes() ){
        _data.resize(_data.size() + len);
        return;
    }
    else{
        //数据前移
        size_t readableLen = readableBytes();
        std::copy(  
            begin()+_readerIndex,
            begin() + _writerIndex,
            begin()+ CHEAPPREPEND);
        _readerIndex = CHEAPPREPEND;
        _writerIndex = _readerIndex + readableLen;

    }
}
#ifndef MUDUO_BASE_BUFFER_HPP
#define MUDUO_BASE_BUFFER_HPP

#include <vector>
#include <string>


/*
 * muduo网络库的网络数据缓冲区
 * 
 */
class Buffer{
public:
    /* 预留的 prependable 空间 */
    static const size_t CHEAPPREPEND = 8;
    /* 默认初始化 缓冲区 的大小*/
    static const size_t INITIALSIZE = 1024;

    /*
    *   initalSize - 指定Buffer的存储大小
    *   默认值为 INITIALSIZE 1024
    */
    explicit Buffer(size_t initalSize = INITIALSIZE);

    /* 缓冲区还可以读的字节大小 */
    size_t readableBytes() const { return _writerIndex - _readerIndex;}
    /* 缓冲区还可写入的字节大小 */
    size_t writableBytes() const { return _data.size() - _writerIndex;}
    /* 缓冲区可在头部插入数据的字节大小*/
    size_t prependableBytes() const { return _readerIndex; }

   
    /* reset缓冲区内 readerindex和 writerIndex 的位置*/
    void retrieve(size_t len);
    void retrieveAll();

    /* 读取缓冲区内数据*/
    std::string retrieveAsString(size_t len);
    std::string retrieveAllAsString();

    /* 将长度为 len 的 数据 写入缓存区 尾部 */
    void append(const char* data,size_t len);

    /* 从 文件 中读取数据 写入缓冲区*/
    ssize_t readFd(int fd,int* saveError);
    /* 将缓冲区数据写入 文件 中*/
    ssize_t writeFd(int fd,int* saveError);

private:
    /* 返回_data底层数组的首地址 */
    char* begin();
    const char* begin() const;
    
    /* 返回缓冲区可写入的数据的地址 */
    char* beginWrite();
    const char* beginWrite() const;

    /* 确保len字节的空间可写入数据,空间不够则扩容 */
    void ensureWritableBytes(size_t len);

    /* 缓冲区可读数据的起始位置 */
    const char* peek() const ;
    /* 重新整合缓冲区数据的分布
    * 1. len + cheapprepend < prependableBytes() + writerableBytes()
    *    则考虑将缓冲区未读数据向前拷贝覆盖掉已读区域,增加可写入区域大小
    * 2. else
    *    则考虑直接vector.resize()
    */
    void makeSpace(size_t len);


private:
    /**
     *     |CHEAPPREPEND|  已读  |     未读    |    可读入     |
     *                      _readerIndex    _writerIndex
     *   begin()                 peek()     beginWrite()
     */
    std::vector<char> _data;
    size_t _readerIndex;
    size_t _writerIndex;

};




#endif

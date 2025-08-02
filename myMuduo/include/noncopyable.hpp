#ifndef NONCOPYABLE_H
#define NONCOPYABLE_H

//用于让派生类不可拷贝构造和复制构造
class noncopyable{
public:
    noncopyable(const noncopyable& ) = delete;
    noncopyable& operator = (const noncopyable&) = delete;

protected:
    noncopyable() = default;
    ~noncopyable() = default;


};


#endif

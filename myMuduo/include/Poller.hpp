#ifndef MUDUO_BASE_POLLER_HPP
#define MUDUO_BASE_POLLER_HPP

#include "TimeStamp.hpp"


#include <unordered_map>
#include <vector>


class Channel;
class EventLoop;


/** muduo库 多路事件分发器的核心IO复用模块 */
class Poller{
public:
    using ChannelList = std::vector<Channel*>;

    Poller(EventLoop* loop)
        :_ownerLoop(loop){}
    virtual ~Poller() = default;

    /** 判断channel是否存在于当前Poller */
    bool hasChannel(Channel* channel) const;
    /** 获取默认的Poller对象 */
    static Poller* newDefaultPoller(EventLoop* loop);

    /** 派生类需要实现的接口 */
    virtual TimeStamp poll(int timeoutMs,ChannelList* avtiveChannels) = 0;
    virtual void updateChannel(Channel* channel) = 0;
    virtual void removeChannel(Channel* channel) = 0;


protected:

    using ChannelMap = std::unordered_map<int,Channel*>;
    /** ( socket_fd ==> socker_fd 所属的channel ) */
    ChannelMap _channels;

private:
    /** Poller 所处的 EventLoop */
    EventLoop* _ownerLoop;


};




#endif

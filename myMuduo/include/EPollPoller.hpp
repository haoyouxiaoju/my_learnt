#ifndef MUDUO_BASE_EPOLLER_HPP
#define MUDUO_BASE_EPOLLER_HPP

#include "Poller.hpp"

#include<sys/epoll.h>
/**
 * Channel的管理主要为状态管理
 * remove Channel不会从容器中删除掉
 * 只会修改Channel的Index为DELTED
 */


class EPollPoller : public Poller{
public:
    EPollPoller(EventLoop* loop);
    ~EPollPoller() override;

    TimeStamp poll(int timeoutMs,ChannelList* avtiveChannels) override;
    void removeChannel(Channel* channel) override;
    void updateChannel(Channel* channel) override;

private:
    static const int InitEventListSize = 16;

    /** 填写活跃的连接 */
    void fillActiveChannels(int numEvents,ChannelList* activeChannels) const;
    /** 更新channel通道 */
    void update(int operation,Channel* chanbel);

    using EventList = std::vector<epoll_event>;


private:
    int _epoll_fd;
    EventList _events;


};




#endif
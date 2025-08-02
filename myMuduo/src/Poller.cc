#include "Poller.hpp"
#include "Channel.hpp"

bool Poller::hasChannel(Channel* channel) const{
    auto ite = _channels.find(channel->fd());
    return ite != _channels.end() && ite->second == channel;
}
// core/EventLoop
#include "core/EventLoop.h"
#include "core/Channel.h"

namespace webserver {

EventLoop::EventLoop()
    : is_looping_(false)
{
}

void EventLoop::loop() {
    is_looping_ = true;
    while (is_looping_) {
        auto active_channels = epoll_.wait();
        handleActiveChannels(active_channels);
    }
}

void EventLoop::handleActiveChannels(std::vector<Channel*> active_channels) {
    for (Channel* ch : active_channels) {
        ch->handleEvent();
    }
}

} // namespace webserver
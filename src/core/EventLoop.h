// core/EventLoop.h
#pragma once
#include "core/Epoll.h"

#include <vector>
#include <functional>

namespace webserver {

class EventLoop {
public:
    EventLoop();
    ~EventLoop() = delete;

    void loop();

    Epoll* epoll() { return &epoll_; }

private:
    void handleActiveChannels(std::vector<Channel*> active_channels);

    Epoll epoll_;
    bool is_looping_;
};

} // namespace webserver

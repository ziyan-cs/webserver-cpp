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
    void handleActiveChannels();

    Epoll epoll_;
    bool is_looping_;
};

} // namespace webserver

// core/Channel.cpp
#include "core/Channel.h"
#include "core/Epoll.h"

namespace webserver {

Channel::Channel(EventLoop* loop, int fd)
    : loop_(loop),
      fd_(fd),
      events_(0),
      revents_(0),
      is_in_epoll_(false)
{
}

void Channel::handleEvent() {
    if (revents_ & EPOLLIN) {
        if (readCallback) readCallback();
    }

    if (revents_ & EPOLLOUT) {
        if (writeCallback) writeCallback();
    }

    if (revents_ & (EPOLLERR | EPOLLHUP)) {
        if (errorCallback) errorCallback();
    }

    if (revents_ & EPOLLRDHUP) {
        if (closeCallback) closeCallback();
    }
}
    
} // namespace webserver
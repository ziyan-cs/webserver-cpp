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
    while (true) {
        std::vector<epoll_event> revents = epoll_.wait(1000);
    
        for (epoll_event ev : revents) {
            ev.data.ptr->handleEvent();
        }
    }
}

void EventLoop::handleActiveChannels() {


}

} // namespace webserver
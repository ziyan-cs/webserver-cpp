// core/Epoll.h
#pragma once

#include <vector>
#include <sys/epoll.h>

namespace webserver {

class Channel;

class Epoll {
public:
    Epoll();
    ~Epoll();

    void addEvent(Channel* ch);
    void delEvent(Channel* ch);

    std::vector<epoll_event> wait(int timeout = -1);
private:
    static const int MAX_EVENTS = 1024;
    int fd_;
    std::vector<epoll_event> revents_;
};

} // namespace webserver
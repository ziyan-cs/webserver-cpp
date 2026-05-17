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

    void updateEvent(Channel* ch);
    void delEvent(Channel* ch);

    std::vector<Channel*> wait(int timeout = -1);
private:
    int fd_;
    std::vector<epoll_event> revents_;
};

} // namespace webserver
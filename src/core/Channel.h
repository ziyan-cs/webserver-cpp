// core/Channel.h
#include <cstdint>

namespace webserver {

class Epoll;

class Channel{
public:
    Channel(Epoll* epoll, int fd);
    ~Channel();

    // Getters
    int fd() const { return fd_; }
    uint32_t events() const { return events_; }
    bool isInEpoll() const { return is_in_epoll_; }

    // Setters
    void setEvents(uint32_t events) { events_ = events; }
    void setInEpoll(bool on) { is_in_epoll_ = on; }
private:
    Epoll* epoll_;
    int fd_;
    uint32_t events_;
    bool is_in_epoll_;
};

}
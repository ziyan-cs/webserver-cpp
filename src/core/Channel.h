// core/Channel.h
#pragma once
#include <cstdint>
#include <functional>
#include <sys/epoll.h>

namespace webserver {

class Epoll;

class Channel{
public:
    // Event callback function type
    using EventCallback = std::function<void()>;

    Channel(Epoll* epoll, int fd);
    ~Channel() = default;

    void handleEvent();

    // Set callback functions
    void setReadCallback(EventCallback cb) { readCallback = std::move(cb); }
    void setWriteCallback(EventCallback cb) { writeCallback = std::move(cb); }
    void setCloseCallback(EventCallback cb) { closeCallback = std::move(cb); }
    void setErrorCallback(EventCallback cb) { errorCallback = std::move(cb); }

    void enableReading() { events_ |= EPOLLIN; }
    void enableWriting() { events_ |= EPOLLOUT; }
    void disableReading() { events_ &= ~EPOLLIN; }
    void disableWriting() { events_ &= ~EPOLLOUT; }
    void disableAll() { events_ = 0; }

    void update() { epoll_->updateEvent(this); }

    // Getters
    int fd() const { return fd_; }
    uint32_t events() const { return events_; }
    uint32_t revents() const { return revents_; }
    bool isInEpoll() const { return is_in_epoll_; }

    // Setters
    void setRevents(uint32_t revents) { revents_ = revents; }
    void setInEpoll(bool in) { is_in_epoll_ = in; }
private:
    Epoll* epoll_;
    int fd_;

    uint32_t events_;
    uint32_t revents_;
    bool is_in_epoll_;

    EventCallback readCallback;
    EventCallback writeCallback;
    EventCallback closeCallback;
    EventCallback errorCallback;
};

} // namespace webserver
// core/Epoll.cpp
#include "log/Logger.h"
#include "core/Epoll.h"
#include "core/Channel.h"

#include <cerrno>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>

namespace webserver {

Epoll::Epoll() {
    fd_ = ::epoll_create1(0);
    if (fd_ == -1) {
        LOG_ERROR("epoll_create1() failed");
        exit(EXIT_FAILURE);
    }
    revents_.resize(MAX_EVENTS);
}

Epoll::~Epoll() {
    if (fd_ != -1) {
        ::close(fd_);
        fd_ = -1;
    }
}

void Epoll::updateEvent(Channel* ch) {
    struct epoll_event ev{};
    ev.events = ch->events();
    ev.data.ptr = ch;

    if (ch->isInEpoll()) {
        if (::epoll_ctl(fd_, EPOLL_CTL_MOD, ch->fd(), &ev) == -1) {
            LOG_ERROR("epoll_ctl() MOD fail for fd=" << ch->fd());
        }
    } else {
        if (::epoll_ctl(fd_, EPOLL_CTL_ADD, ch->fd(), &ev) == -1) {
            LOG_ERROR("epoll_ctl() ADD fail for fd=" << ch->fd());
            return;
        }
        ch->setInEpoll(true);
    }
}

void Epoll::delEvent(Channel* ch) {
    if (ch->isInEpoll()) {
        if (::epoll_ctl(fd_, EPOLL_CTL_DEL, ch->fd(), nullptr) == -1) {
            LOG_ERROR("epoll_ctl() DEL fail for fd=" << ch->fd());
            return;
        }
        ch->setInEpoll(false);
    }
}

std::vector<Channel*> Epoll::wait(int timeout) {
    std::vector<Channel*> activeChannels;
    int num = ::epoll_wait(fd_, revents_.data(), revents_.size(), timeout);

    for (int i = 0; i < num; ++i) {
        Channel* ch = static_cast<Channel*>(revents_[i].data.ptr);
        ch->setRevents(revents_[i].events);
        activeChannels.push_back(ch);
    }
    return activeChannels;
}

} // namespace webserver
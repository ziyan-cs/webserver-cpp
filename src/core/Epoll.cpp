#include "core/Epoll.h"

#include <cerrno>
#include <system_error>
#include <unistd.h>

namespace core {

Epoll::Epoll() : fd_(epoll_create1(EPOLL_CLOEXEC)) {
  if (fd_ < 0) {
    const int error = errno;
    throw std::system_error(error, std::generic_category(), "epoll_create1");
  }
}

bool Epoll::add(int fd, uint32_t events) {
  epoll_event ev{};
  ev.events = events;
  ev.data.fd = fd;

  int ret = ::epoll_ctl(fd_, EPOLL_CTL_ADD, fd, &ev);
  if (ret < 0)
    return false;
  return true;
}

bool Epoll::mod(int fd, uint32_t events) {
  epoll_event ev{};
  ev.events = events;
  ev.data.fd = fd;

  int ret = ::epoll_ctl(fd_, EPOLL_CTL_MOD, fd, &ev);
  if (ret < 0)
    return false;
  return true;
}

bool Epoll::del(int fd) {
  int ret = ::epoll_ctl(fd_, EPOLL_CTL_DEL, fd, nullptr);
  if (ret < 0)
    return false;
  return true;
}

std::vector<epoll_event> Epoll::wait(int time_out_ms) {
  events_.resize(64);
  while (true) {
    int n = ::epoll_wait(fd_, events_.data(), static_cast<int>(events_.size()), time_out_ms);
    if (n < 0) {
      if (errno != EINTR)
        return {};
      continue;
    }
    events_.resize(n);
    return events_;
  }
}

void Epoll::close() {
  if (fd_ >= 0) {
    ::close(fd_);
    fd_ = -1;
  }
}

}  // namespace core

#pragma once

#include <sys/epoll.h>
#include <vector>

namespace core {

// Owns an epoll instance and manages its monitored file descriptors.
class Epoll {
 public:
  Epoll();
  ~Epoll() { close(); }

  // Movable but not copyable.
  Epoll(const Epoll&) = delete;
  Epoll& operator=(const Epoll&) = delete;
  Epoll(Epoll&& other) noexcept : fd_(other.fd_) { other.fd_ = -1; }
  Epoll& operator=(Epoll&& other) noexcept {
    if (this != &other) {
      close();
      fd_ = other.fd_;
      other.fd_ = -1;
    }
    return *this;
  }

  // Return whether the registration operation succeeded.
  bool add(int fd, uint32_t event);
  bool mod(int fd, uint32_t event);
  bool del(int fd);

  // Wait indefinitely by default; return an empty vector on timeout or error.
  std::vector<epoll_event> wait(int time_out_ms = -1);

 private:
  void close();

  int fd_ = -1;
  std::vector<epoll_event> events_;
};

}  // namespace core

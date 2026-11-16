#pragma once

#include <sys/socket.h>
#include <sys/types.h>

namespace net {

class InetAddress;

class Socket {
 public:
  Socket();
  explicit Socket(int fd) : fd_(fd) {}
  ~Socket() { close(); }

  // Movable but not copyable.
  Socket(const Socket&) = delete;
  Socket& operator=(const Socket&) = delete;
  Socket(Socket&& other) noexcept : fd_(other.fd_) { other.fd_ = -1; }
  Socket& operator=(Socket&& other) noexcept {
    if (this != &other) {
      close();
      fd_ = other.fd_;
      other.fd_ = -1;
    }
    return *this;
  }

  void bind(const InetAddress& local_addr);
  void listen(int bocklog);
  int accept(InetAddress* peer_addr);

  ssize_t read(char* buf, size_t len) { return recv(fd_, buf, len, 0); }
  ssize_t write(const char* buf, size_t len) { return send(fd_, buf, len, MSG_NOSIGNAL); }

  void close();

  void reuseAddr(bool on);
  void reusePort(bool on);

  [[nodiscard]] int fd() const { return fd_; }

 private:
  int fd_ = -1;
};

}  // namespace net

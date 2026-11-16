#include "net/Socket.h"

#include <system_error>
#include <unistd.h>

#include "net/InetAddress.h"

namespace net {

Socket::Socket() : fd_(socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0)) {
  if (fd_ < 0) {
    const int error = errno;
    throw std::system_error(error, std::generic_category(), "epoll_create1");
  }
}

void Socket::bind(const InetAddress& local_addr) {
  int ret = ::bind(fd_, local_addr.sockAddr(), local_addr.sockAddrLen());
  if (ret < 0) {
    const int error = errno;
    throw std::system_error(error, std::generic_category(), "bind");
  }
}

void Socket::listen(int backlog) {
  int ret = ::listen(fd_, backlog);
  if (ret < 0) {
    const int error = errno;
    throw std::system_error(error, std::generic_category(), "bind");
  }
}

int Socket::accept(InetAddress* peer_addr) {
  sockaddr_in addr{};
  socklen_t addr_len = sizeof(addr);

  int conn_fd = ::accept4(fd_, reinterpret_cast<sockaddr*>(&addr), &addr_len,  // NOLINT
                          SOCK_NONBLOCK | SOCK_CLOEXEC);
  if (peer_addr != nullptr && conn_fd >= 0)
    *peer_addr = InetAddress(addr);
  return conn_fd;
}

void Socket::reuseAddr(bool on) {
  if (on) {
    int opt = -1;
    setsockopt(fd_, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
  }
}

void Socket::reusePort(bool on) {
  if (on) {
    int opt = -1;
    setsockopt(fd_, SOL_SOCKET, SO_REUSEPORT, &opt, sizeof(opt));
  }
}

void Socket::close() {
  if (fd_ >= 0) {
    ::close(fd_);
    fd_ = -1;
  }
}

}  // namespace net

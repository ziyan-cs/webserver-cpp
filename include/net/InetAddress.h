#pragma once

#include <netinet/in.h>
#include <string>

namespace net {

class InetAddress {
 public:
  InetAddress() = default;
  InetAddress(const std::string& ip, uint16_t port);
  explicit InetAddress(const sockaddr_in& addr) : addr_(addr) {}
  ~InetAddress() = default;

  // Neither copyable nor movable.
  InetAddress(const InetAddress&) = default;
  InetAddress& operator=(const InetAddress&) = default;
  InetAddress(InetAddress&&) = default;
  InetAddress& operator=(InetAddress&&) = default;

  [[nodiscard]] std::string ip() const;
  [[nodiscard]] uint16_t port() const { return ntohs(addr_.sin_port); }
  [[nodiscard]] std::string toString() const { return ip() + ":" + std::to_string(port()); }
  [[nodiscard]] socklen_t sockAddrLen() const { return sizeof(addr_); }
  [[nodiscard]] const sockaddr* sockAddr() const noexcept {
    return reinterpret_cast<const sockaddr*>(&addr_);  // NOLINT
  }

 private:
  sockaddr_in addr_{};
};

}  // namespace net

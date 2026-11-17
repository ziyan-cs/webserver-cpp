#include "net/InetAddress.h"

#include <arpa/inet.h>
#include <system_error>

namespace net {

InetAddress::InetAddress(const std::string& ip, uint16_t port) {
  addr_.sin_family = AF_INET;
  addr_.sin_port = htons(port);

  int ret = inet_pton(AF_INET, ip.c_str(), &addr_.sin_addr);
  if (ret == 0) {
    throw std::invalid_argument("Invalid IPv4 address: " + ip);
  } else if (ret == -1) {
    const int error = errno;
    throw std::system_error(error, std::generic_category(), "InetAddress::InetAddress");
  }
}

[[nodiscard]] std::string InetAddress::ip() const {
  char buf[INET_ADDRSTRLEN]{};

  const char* ret = inet_ntop(AF_INET, &addr_.sin_addr, buf, sizeof(buf));
  if (ret == nullptr) {
    const int error = errno;
    throw std::system_error(error, std::generic_category(), "InetAddress::ip");
  }

  return buf;
}

}  // namespace net

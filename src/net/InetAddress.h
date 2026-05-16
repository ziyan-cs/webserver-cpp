// net/InetAddress
#pragma once

#include <string>
#include <arpa/inet.h>

namespace webserver {

class InetAddress {
public:
    sockaddr_in addr_;

    InetAddress(uint16_t port) {
        addr_.sin_family = AF_INET;
        addr_.sin_addr.s_addr = htonl(INADDR_ANY);
        addr_.sin_port = htons(port);
    }

    InetAddress() {}

    const sockaddr* sockAddr() const { return (sockaddr*)&addr_; }
    sockaddr* sockAddr() { return (sockaddr*)&addr_; }

    std::string ip() const {
        char buffer[32];
        inet_ntop(AF_INET, &addr_.sin_addr, buffer, sizeof(buffer));
        return buffer;
    }

    uint16_t port() const {
        return ntohs(addr_.sin_port);
    }
};

} // namespace webserverclass
// net/Socket.cpp
#include "log/Logger.h"
#include "net/Socket.h"

#include <cerrno>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

namespace webserver {

Socket::Socket() {
    fd_ = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (fd_ == -1) {
        LOG_ERROR("::socket() failed");
        std::exit(EXIT_FAILURE);
    }
}

Socket::Socket(int fd)
    : fd_(fd)
{
}


Socket::~Socket() {
    if (fd_ != -1) {
        ::close(fd_);
        fd_ = -1;
    }
}

void Socket::bindSock(int port, std::string ip) {
    struct sockaddr_in server_addr{};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    if(ip == "0.0.0.0") {
        server_addr.sin_addr.s_addr = INADDR_ANY;
    } else {
        if (::inet_pton(AF_INET, ip.c_str(), &server_addr.sin_addr) <= 0) {
            LOG_ERROR("::inet_pton() failed for ip=" << ip);
        }
        std::exit(EXIT_FAILURE);
    }
    
    if (::bind(fd_, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        LOG_ERROR("::bind() failed for ip=" << ip);
        std::exit(EXIT_FAILURE);
    }
}

void Socket::listenSock(int backlog) {
    if (::listen(fd_, backlog) == -1) {
        LOG_ERROR("::listen() failed for fd=" << fd_);
        std::exit(EXIT_FAILURE);
    }
}

} // namespace webserver
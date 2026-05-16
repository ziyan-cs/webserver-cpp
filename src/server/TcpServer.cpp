// server/TcpServer.cpp
#include "log/Logger.h"
#include "server/TcpServer.h"

#include <vector>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <fcntl.h>

namespace webserver {

TcpServer::TcpServer(const Config& config)
    : config_(config)
{
}

TcpServer::~TcpServer() {
    // None
}

void TcpServer::start() {
    init();
    run();
}

void TcpServer::init() {
    listen_socket_.bindSock(config_.port(), config_.ip());
    listen_socket_.listenSock(config_.backlog());
    LOG_INFO("Server init succeeded");
}

void TcpServer::run() {
    int buffer_size = config_.bufferSize();
    std::vector<char> buffer(buffer_size);

    while (true) {
        int connect_fd = listen_socket_.acceptSock();
        if (connect_fd == -1) continue;
        LOG_INFO("new client connected, fd=" << connect_fd);
        
        while (true) {
            std::fill(buffer.begin(), buffer.end(), 0);
            ssize_t n = recv(connect_fd, buffer.data(), buffer_size, 0);
            if (n < 0) {
                LOG_ERROR("recv() failed for fd=" << connect_fd); 
                ::close(connect_fd);
                break;
            } else if (n == 0) {
                LOG_INFO("client closed connection, fd=" << connect_fd);
                ::close(connect_fd);
                break;
            } else {
                buffer[n] = '\0';
                LOG_INFO("recv: " << buffer.data() << " from fd=" <<connect_fd);
                send(connect_fd, buffer.data(), n, 0);
            }
        }
    }
}

} // namespace webserver
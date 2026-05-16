// server/TcpServer.cpp
#include "log/Logger.h"
#include "server/TcpServer.h"

#include <vector>
#include <algorithm>
#include <errno.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <signal.h>

bool g_running = false;

void signalHandler(int sig) {
    if (sig == SIGINT) {
        LOG_INFO("Received SIGINT, server shutting down gracefully...");
        g_running = false;
    }
}

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
    signal(SIGINT, signalHandler);
    g_running = true;

    int buffer_size = config_.bufferSize();
    std::vector<char> buffer(buffer_size);

    while (g_running) {
        int connect_fd = listen_socket_.acceptSock();
        if (connect_fd == -1) {
            if (errno == EINTR && !g_running) {
                break;
            }
            continue;
        }
        LOG_INFO("new client connected, fd=" << connect_fd);
        
        while (g_running) {
            std::fill(buffer.begin(), buffer.end(), 0);
            ssize_t n = recv(connect_fd, buffer.data(), buffer_size, 0);
            if (n < 0) {
                if (errno == EINTR && !g_running) {
                    break;
                }
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
        ::close(connect_fd);
    }
    ::close(listen_socket_.fd());
    LOG_INFO("Server stopped");
}

} // namespace webserver
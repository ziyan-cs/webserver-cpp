// net/TcpConnection.cpp
#include "log/Logger.h"
#include "config/Config.h"
#include "core/Channel.h"
#include "net/Socket.h"
#include "net/TcpConnection.h"

namespace webserver {

TcpConnection::TcpConnection(EventLoop* loop, int fd, const InetAddress& addr)
    : loop_(loop), fd_(fd), addr_(addr)
{
    connect_channel_ = new Channel(loop_, fd_);
    connect_channel_->setReadCallback(std::bind(&TcpConnection::handleRead, this));
    connect_channel_->setWriteCallback(std::bind(&TcpConnection::handleWrite, this));
    connect_channel_->setCloseCallback(std::bind(&TcpConnection::handleClose, this));
}

TcpConnection::~TcpConnection() {
    if (connect_channel_) {
        delete connect_channel_;
        connect_channel_ = nullptr;
    }
}

void TcpConnection::handleRead() {
    std::vector<char> buffer(webserver::BUFFER_SIZE);
    std::fill(buffer.begin(), buffer.end(), 0);
    ssize_t n = ::recv(fd_, buffer.data(), buffer.size() -1, 0);

    if (n < 0) {
        if (errno != EINTR) {
            LOG_ERROR("recv() failed for fd=" << fd_); 
            handleClose();
        }
    } else if (n == 0) {
        LOG_INFO("client closed connection, fd=" << fd_);
        handleClose();
    } else {
        LOG_INFO("recv: " << buffer.data() << " from fd=" << fd_);
    }
}

void TcpConnection::handleWrite() {
    std::string msg = "Hello from server";
    size_t len = sizeof(msg);
    size_t n = ::send(fd_, msg.data(), len -1, 0);
 
    if (n < 0) {
        LOG_ERROR("send() failed for fd=" << fd_); 
        handleClose();
    } else if (n = 0) {
        LOG_ERROR("send() failed for fd=" << fd_);
        handleClose();
    } else {
        LOG_INFO("send " << n << " bytes success");
    }
}

void TcpConnection::handleClose() {
    LOG_INFO("client close connection, fd=" << fd_);

    loop_->epoll_.delEvent(connect_channel_);

}

} // namespace webserver
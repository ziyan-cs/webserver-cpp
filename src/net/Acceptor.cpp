// net/Acceptor.cpp
#include "log/Logger.h"
#include "core/Channel.h"
#include "net/Socket.h"
#include "net/Acceptor.h"

namespace webserver {

Acceptor::Acceptor(EventLoop* loop, int fd, const InetAddress& addr)
    : loop_(loop), fd_(fd), addr_(addr)
{
    accept_channel_ = new Channel(loop_, fd_);
    accept_channel_->setReadCallback(std::bind(&Acceptor::handleAccept, this));
    accept_channel_->enableReading();
}

Acceptor::~Acceptor() {
    if (accept_channel_) {
        delete accept_channel_;
        accept_channel_ = nullptr;
    }
}

void Acceptor::handleAccept() {
    InetAddress connect_addr;
    socklen_t len = sizeof(connect_addr);

    int connect_fd = ::accept(fd_, connect_addr.sockAddr(), &len);
    if (connect_fd == -1) {
        LOG_ERROR("accept() failed for fd=" << connect_fd);
    }

}

} // namespace webserver
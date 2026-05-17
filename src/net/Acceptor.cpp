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
}

Acceptor::~Acceptor() {
    if (accept_channel_) {
        delete accept_channel_;
        accept_channel_ = nullptr;
    }
}

void Acceptor::handleAccept() {
    InetAddress client_addr;
    socklen_t len = sizeof(client_addr);

    int client_fd = ::accept(fd_, client_addr.sockAddr(), &len);
    if (client_fd == -1) {
        LOG_ERROR("accept() failed for fd=" << client_fd);
    }
}

} // namespace webserver
// net/Acceptor.cpp
#include "core/Channel.h"
#include "net/Socket.h"
#include "net/Acceptor.h"

namespace webserver {

Acceptor::Acceptor(EventLoop* loop, int fd)
    : loop_(loop), fd_(fd)
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
    int connect_fd = 
    int flags = fcntl(fd_, F_GETFL, 0);
    fcntl(client_fd, F_SETFL, flags | O_NONBLOCK);
    LOGI("New client connected, fd=" + std::to_string(client_fd));
}

} // namespace webserver
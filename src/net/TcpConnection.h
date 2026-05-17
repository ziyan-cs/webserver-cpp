// net/TcpConnection.h
#pragma once
#include "net/Socket.h"
#include "net/InetAddress.h"

namespace webserver {

class EventLoop;

class Channel;

class TcpConnection {
public:
    TcpConnection(EventLoop* loop, int fd, const InetAddress& addr_);
    ~TcpConnection();

private:
    void handleRead();
    void handleWrite();
    void handleClose();

    EventLoop* loop_;
    int fd_;
    InetAddress addr_;
    Channel* connect_channel_;
};

} // namespace webserver
// net/Acceptor.h
#pragma once
#include "net/Socket.h"
#include "net/InetAddress.h"

namespace webserver {

class EventLoop;

class Channel;

class Acceptor {
public:
    Acceptor(EventLoop* loop, int fd, const InetAddress& addr);
    ~Acceptor();

private:
    void handleAccept();

    EventLoop* loop_;
    int fd_;
    InetAddress addr_;
    Channel* accept_channel_;
};


} // namespace webserver

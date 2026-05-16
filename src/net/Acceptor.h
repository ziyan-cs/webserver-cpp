// net/Acceptor.h
#pragma once
#include "net/Socket.h"

namespace webserver {

class EventLoop;

class Channel;

class Acceptor {
public:
    Acceptor();
    ~Acceptor() = delete;


private:
    EventLoop* loop_;
    int fd_;
    Channel* accept_channel_;
};


} // namespace webserver

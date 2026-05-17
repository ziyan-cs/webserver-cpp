// net/Acceptor.h
#pragma once
#include "net/Socket.h"
#include "net/InetAddress.h"

namespace webserver {

class EventLoop;

class Channel;

class Acceptor {
public:
    using NewConnectionCallback = std::function<void(int)>;

    Acceptor(EventLoop* loop, int fd, const InetAddress& addr);
    ~Acceptor();

    void setNewConnectionCallback(NewConnectionCallback cb) { newConnectionCallback_ = std::move(cb); }
private:
    void handleAccept();

    NewConnectionCallback newConnectionCallback_;

    EventLoop* loop_;
    int fd_;
    InetAddress addr_;
    Channel* accept_channel_;
};


} // namespace webserver

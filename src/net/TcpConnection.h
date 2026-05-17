// net/TcpConnection.h
#pragma once
#include "net/Socket.h"
#include "net/InetAddress.h"

#include <functional>

namespace webserver {

class EventLoop;

class Channel;

class TcpConnection {
public:
    using MessageCallback = std::function<void(const std::string msg)>;
    using ConnectionCloseCallback = std::function<void(TcpConnection*)>;
    using ConnectionErrorCallback = std::function<void(TcpConnection*)>;

    TcpConnection(EventLoop* loop, int fd, const InetAddress& addr_);
    ~TcpConnection();

    void setMessageCallback(MessageCallback cb) { messageCallback_ = std::move(cb); }
    void setConnectionCloseCallback(ConnectionCloseCallback cb) { connectionCloseCallback_ = std::move(cb); }
    void setConnectionErrorCallback(ConnectionErrorCallback cb) { connectionErrorCallback_ = std::move(cb); }
private:
    void handleRead();
    void handleWrite();
    void handleClose();

    MessageCallback messageCallback_;
    ConnectionCloseCallback connectionCloseCallback_;
    ConnectionErrorCallback connectionErrorCallback_;

    EventLoop* loop_;
    int fd_;
    InetAddress addr_;
    Channel* connect_channel_;
};

} // namespace webserver
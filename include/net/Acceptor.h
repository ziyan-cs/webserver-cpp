#pragma once

#include <functional>
#include <memory>

#include "core/Channel.h"
#include "core/EventLoop.h"
#include "net/InetAddress.h"
#include "net/Socket.h"

namespace net {

class Acceptor {
 public:
  static const int kMaxAcceptorPerLoop = 128;

  // The callback takes ownership of the accepted fd.
  using NewConnectionCallback = std::function<void(int fd, const InetAddress addr)>;

  Acceptor(core::EventLoop* loop, const InetAddress& addr)
      : addr_(addr),
        loop_(loop),
        socket_(std::make_unique<Socket>()),
        channel_(std::make_unique<core::Channel>(socket_->fd(), loop_)) {}
  ~Acceptor() = default;

  void setOnNewConnection(NewConnectionCallback cb) { new_conn_cb_ = std::move(cb); }

  void start();
  void stop();

  [[nodiscard]] int fd() const { return socket_->fd(); }

 private:
  void handleRead();

  InetAddress addr_;
  core::EventLoop* loop_ = nullptr;
  std::unique_ptr<net::Socket> socket_;
  std::unique_ptr<core::Channel> channel_;
  bool listening_ = false;
  bool started_ = false;
  NewConnectionCallback new_conn_cb_;
};

}  // namespace net

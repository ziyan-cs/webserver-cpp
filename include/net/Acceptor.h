#pragma once

#include <functional>
#include <memory>

#include "base/Config.h"
#include "core/Channel.h"
#include "core/EventLoop.h"
#include "net/InetAddress.h"
#include "net/Socket.h"

namespace net {

class Acceptor {
 public:
  static const int kMaxAcceptorPerLoop = 128;

  // The callback takes ownership of the accepted fd.
  using NewConnectionCallback =
      std::function<void(std::unique_ptr<Socket> socket, const InetAddress& addr)>;

  Acceptor(core::EventLoop* loop, const InetAddress& addr)
      : addr_(addr),
        loop_(loop),
        socket_(std::make_unique<Socket>()),
        channel_(std::make_unique<core::Channel>(socket_->fd(), loop_)) {
    socket_->reuseAddr(true);
    socket_->bind(addr_);
    socket_->listen(base::Config::instance().backlog());
    channel_->setOnRead([this] { handleRead(); });
    channel_->setOnClose([this] { stop(); });
  }
  ~Acceptor() {
    channel_->setOnRead({});
    channel_->setOnClose({});
  }

  // Neither copyable nor movable.
  Acceptor(const Acceptor&) = delete;
  Acceptor& operator=(const Acceptor&) = delete;
  Acceptor(Acceptor&&) = delete;
  Acceptor& operator=(Acceptor&&) = delete;

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

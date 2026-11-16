#pragma once

#include <unordered_map>
#include <unordered_set>

#include "core/EventLoop.h"
#include "net/Acceptor.h"
#include "net/TcpConnection.h"

namespace net {

class TcpServer {
 public:
  TcpServer(core::EventLoop* loop, const InetAddress& addr)
      : loop_(loop), acceptor_(std::make_unique<Acceptor>(loop_, addr)) {
    acceptor_->setOnNewConnection([this](std::unique_ptr<Socket> socket, const InetAddress& addr) {
      handleNewConnection(std::move(socket), addr);
    });
    loop_->setOnErase([this] { handleErase(); });
  }
  ~TcpServer() {
    acceptor_->setOnNewConnection({});
    loop_->setOnErase({});
  }

  // Neither copyable nor movable.
  TcpServer(const TcpServer&) = delete;
  TcpServer& operator=(const TcpServer&) = delete;
  TcpServer(TcpServer&&) = delete;
  TcpServer& operator=(TcpServer&&) = delete;

  void start();
  void stop();

  bool started() const { return started_; }

 private:
  void handleNewConnection(std::unique_ptr<Socket> socket, const InetAddress& addr);
  void handleMessage(int fd);
  void handleClose(int fd);
  void handleErase();

  core::EventLoop* loop_;
  std::unique_ptr<Acceptor> acceptor_;
  std::unordered_map<int, std::unique_ptr<TcpConnection>> tcp_connections_;
  std::unordered_set<TcpConnection*> pending_removals_;
  bool started_ = false;
};

}  // namespace net

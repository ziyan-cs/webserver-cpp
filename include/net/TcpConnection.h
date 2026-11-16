#pragma once

#include <functional>
#include <memory>
#include <string_view>

#include "base/Buffer.h"
#include "core/Channel.h"
#include "net/InetAddress.h"
#include "net/Socket.h"

namespace net {

class TcpConnection {
 public:
  // Callbacks must not destroy this connection during event dispatch.
  using MessageCallback = std::function<void(int fd)>;
  using CloseCallback = std::function<void(int fd)>;

  TcpConnection(core::EventLoop* loop, std::unique_ptr<Socket> socket, const InetAddress addr)
      : addr_(addr),
        loop_(loop),
        socket_(std::move(socket)),
        channel_(std::make_unique<core::Channel>(socket_->fd(), loop_)) {
    channel_->setOnRead([this] { handleRead(); });
    channel_->setOnWrite([this] { handleWrite(); });
    channel_->setOnClose([this] { handleClose(); });
  }
  ~TcpConnection() {
    channel_->setOnRead({});
    channel_->setOnWrite({});
    channel_->setOnClose({});
  }

  // Neither copyable nor movable.
  TcpConnection(const TcpConnection&) = delete;
  TcpConnection& operator=(const TcpConnection&) = delete;
  TcpConnection(TcpConnection&&) = delete;
  TcpConnection& operator=(TcpConnection&&) = delete;

  void setOnMessage(MessageCallback cb) { message_cb_ = std::move(cb); }
  void setOnClose(CloseCallback cb) { close_cb_ = std::move(cb); }

  void start();
  void close() { handleClose(); }
  void send(std::string_view data);
  base::Buffer& inputBuffer() { return input_buffer_; }

  [[nodiscard]] int fd() const { return socket_->fd(); }

 private:
  void handleRead();
  void handleWrite();
  void handleClose();

  InetAddress addr_;
  core::EventLoop* loop_ = nullptr;
  std::unique_ptr<net::Socket> socket_;
  std::unique_ptr<core::Channel> channel_;
  base::Buffer input_buffer_;
  base::Buffer output_buffer_;
  bool connected_ = false;
  bool closed_ = false;
  MessageCallback message_cb_;
  CloseCallback close_cb_;
};

}  // namespace net

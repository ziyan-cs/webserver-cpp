#include "net/TcpServer.h"

#include "base/Logger.h"

namespace net {

void TcpServer::start() {
  if (started_)
    return;

  acceptor_->start();
  started_ = true;
}

void TcpServer::stop() {
  if (!started_)
    return;

  acceptor_->stop();
  started_ = false;
}

void TcpServer::handleNewConnection(std::unique_ptr<Socket> socket, const InetAddress& addr) {
  int fd = socket->fd();
  auto it = tcp_connections_.find(fd);
  if (it != tcp_connections_.end())
    return;

  base::Logger::instance().log(base::Logger::LogLevel::INFO,
                               "New Connection from: " + addr.toString());
  auto tcp_connection = std::make_unique<TcpConnection>(loop_, std::move(socket), addr);
  tcp_connection->setOnMessage([this](int fd) { handleMessage(fd); });
  tcp_connection->setOnClose([this](int fd) { handleClose(fd); });
  tcp_connections_[fd] = std::move(tcp_connection);
  tcp_connections_[fd]->start();
}

void TcpServer::handleMessage(int fd) {}

void TcpServer::handleClose(int fd) {
  auto it = tcp_connections_.find(fd);
  if (it == tcp_connections_.end())
    return;

  pending_removals_.insert(it->second.get());
}

void TcpServer::handleErase() {
  for (auto* connection : pending_removals_) {
    for (auto it = tcp_connections_.begin(); it != tcp_connections_.end(); ++it) {
      if (it->second.get() == connection) {
        tcp_connections_.erase(it);
        break;
      }
    }
  }
  pending_removals_.clear();
}

}  // namespace net

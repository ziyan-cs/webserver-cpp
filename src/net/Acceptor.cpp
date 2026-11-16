#include "net/Acceptor.h"

#include <cerrno>
#include <stdexcept>
#include <unistd.h>

#include "base/Config.h"
#include "base/Logger.h"

namespace net {

void Acceptor::start() {
  if (started_)
    return;

  if (!listening_) {
    socket_->reuseAddr(true);
    socket_->bind(addr_);
    socket_->listen(base::Config::instance().backlog());
    listening_ = true;
  }

  channel_->setOnRead([this] { handleRead(); });
  channel_->setOnClose([this] { stop(); });
  channel_->enableReading();
  if (!channel_->update())
    throw std::runtime_error("Failed to register acceptor channel");
  started_ = true;
}

void Acceptor::stop() {
  if (!started_)
    return;
  channel_->disableReading();
  bool removed = channel_->remove();
  started_ = false;
  if (!removed)
    base::Logger::instance().log(base::Logger::LogLevel::ERROR, "Failed to remove acceptor channel");
}

void Acceptor::handleRead() {
  for (int i = 0; i < kMaxAcceptorPerLoop; ++i) {
    InetAddress peer_addr;
    int fd = socket_->accept(&peer_addr);

    if (fd < 0) {
      if (errno == EINTR)
        continue;
      if (errno != EAGAIN && errno != EWOULDBLOCK)
        base::Logger::instance().log(base::Logger::LogLevel::ERROR, "Failed to accept connection");
      break;
    }

    if (new_conn_cb_)
      new_conn_cb_(fd, peer_addr);
    else
      ::close(fd);
  }
}

}  // namespace net

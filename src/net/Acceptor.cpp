#include "net/Acceptor.h"

#include <cerrno>
#include <stdexcept>
#include <system_error>
#include <unistd.h>

#include "base/Logger.h"

namespace net {

void Acceptor::start() {
  if (started_)
    return;

  channel_->enableReading();
  if (!channel_->update()) {
    throw std::runtime_error("Acceptor::start: channel update failed, fd=" +
                             std::to_string(socket_->fd()));
  }
  started_ = true;
}

void Acceptor::stop() {
  if (!started_)
    return;

  channel_->disableReading();
  bool removed = channel_->remove();
  started_ = false;
  if (!removed)
    base::Logger::instance().log(
        base::Logger::LogLevel::ERROR,
        "Acceptor::stop: channel removal failed, fd=" + std::to_string(socket_->fd()));
}

void Acceptor::handleRead() {
  for (int i = 0; i < kMaxAcceptorPerLoop; ++i) {
    InetAddress peer_addr;
    int fd = socket_->accept(&peer_addr);

    if (fd >= 0) {
      auto socket = std::make_unique<Socket>(fd);
      if (new_conn_cb_)
        new_conn_cb_(std::move(socket), peer_addr);
    } else if (errno == EINTR) {
      continue;
    } else if (errno == EAGAIN || errno == EWOULDBLOCK) {
      break;
    } else {
      const int error = errno;
      throw std::system_error(error, std::generic_category(),
                              "Acceptor::handleRead fd=" + std::to_string(socket_->fd()));
    }
  }
}

}  // namespace net

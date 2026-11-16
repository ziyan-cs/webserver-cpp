#include "net/TcpConnection.h"

#include <cerrno>
#include <stdexcept>
#include <system_error>

#include "base/Logger.h"

namespace net {

void TcpConnection::start() {
  if (connected_)
    return;
  if (closed_)
    throw std::logic_error("TcpConnection::start: connection is closed, peer=" + addr_.toString());

  channel_->enableReading();
  if (!channel_->update()) {
    throw std::runtime_error("TcpConnection::start: channel update failed, peer=" +
                             addr_.toString());
  }
  connected_ = true;
}

void TcpConnection::send(std::string_view data) {
  if (!connected_ || data.empty())
    return;

  output_buffer_.append(data.data(), data.size());
  channel_->enableWriting();
  if (!channel_->update()) {
    base::Logger::instance().log(
        base::Logger::LogLevel::ERROR,
        "TcpConnection::send: channel update failed, peer=" + addr_.toString());
    handleClose();
  }
}

void TcpConnection::handleRead() {
  if (!connected_)
    return;
  char buf[4096];
  while (connected_) {
    const auto n = socket_->read(buf, sizeof(buf));
    if (n > 0) {
      input_buffer_.append(buf, n);
      if (message_cb_)
        message_cb_(socket_->fd());
    } else if (n == 0) {
      handleClose();
      return;
    } else if (errno == EINTR) {
      continue;
    } else if (errno == EAGAIN || errno == EWOULDBLOCK) {
      return;
    } else {
      const int error = errno;
      base::Logger::instance().log(
          base::Logger::LogLevel::ERROR,
          "TcpConnection::handleRead: peer=" + addr_.toString() +
              ", error=" + std::error_code(error, std::generic_category()).message());
      handleClose();
      return;
    }
  }
}

void TcpConnection::handleWrite() {
  while (connected_ && output_buffer_.readableBytes() != 0) {
    const auto n = socket_->write(output_buffer_.peek(), output_buffer_.readableBytes());
    if (n > 0) {
      output_buffer_.consume(static_cast<std::size_t>(n));
    } else if (n < 0 && errno == EINTR) {
      continue;
    } else if (n < 0 && (errno == EAGAIN || errno == EWOULDBLOCK)) {
      return;
    } else {
      const int error = n < 0 ? errno : 0;
      base::Logger::instance().log(
          base::Logger::LogLevel::ERROR,
          "TcpConnection::handleWrite: peer=" + addr_.toString() + ", error=" +
              (n < 0 ? std::error_code(error, std::generic_category()).message() : "no progress"));
      handleClose();
      return;
    }
  }

  if (connected_) {
    channel_->disableWriting();
    if (!channel_->update()) {
      base::Logger::instance().log(
          base::Logger::LogLevel::ERROR,
          "TcpConnection::handleWrite: channel update failed, peer=" + addr_.toString());
      handleClose();
    }
  }
}

void TcpConnection::handleClose() {
  if (!connected_)
    return;
  connected_ = false;
  closed_ = true;
  channel_->remove();
  if (close_cb_)
    close_cb_(socket_->fd());
  socket_->close();
}

}  // namespace net

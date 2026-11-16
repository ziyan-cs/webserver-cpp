#include "net/TcpConnection.h"

#include <cerrno>
#include <stdexcept>

namespace net {

void TcpConnection::start() {
  if (connected_)
    return;
  if (closed_)
    throw std::logic_error("Cannot restart a closed connection");

  channel_->setOnRead([this] { handleRead(); });
  channel_->setOnWrite([this] { handleWrite(); });
  channel_->setOnClose([this] { handleClose(); });
  channel_->enableReading();
  if (!channel_->update())
    throw std::runtime_error("Failed to register connection channel");
  connected_ = true;
}

void TcpConnection::send(std::string_view data) {
  if (!connected_ || data.empty())
    return;
  output_buffer_.append(data.data(), data.size());
  channel_->enableWriting();
  if (!channel_->update())
    handleClose();
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
        message_cb_();
    } else if (n < 0 && errno == EINTR) {
      continue;
    } else if (n < 0 && (errno == EAGAIN || errno == EWOULDBLOCK)) {
      return;
    } else {
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
      handleClose();
      return;
    }
  }
  if (connected_) {
    channel_->disableWriting();
    if (!channel_->update())
      handleClose();
  }
}

void TcpConnection::handleClose() {
  if (!connected_)
    return;
  connected_ = false;
  closed_ = true;
  channel_->remove();
  socket_->close();
  if (close_cb_)
    close_cb_();
}

}  // namespace net

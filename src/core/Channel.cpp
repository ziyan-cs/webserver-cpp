#include "core/Channel.h"

#include "core/EventLoop.h"

namespace core {

bool Channel::update() {
  if (loop_ != nullptr)
    return loop_->updateChannel(this);
  return false;
}

bool Channel::remove() {
  if (loop_ != nullptr)
    return loop_->removeChannel(this);
  return false;
}

void Channel::handleEvent() {
  if ((revents_ & (kReadEvent | EPOLLRDHUP)) != 0) {
    if (read_cb_)
      read_cb_();
  }

  if ((revents_ & (EPOLLHUP | EPOLLERR)) != 0) {
    if (close_cb_)
      close_cb_();
  }

  if ((revents_ & kWriteEvent) != 0) {
    if (write_cb_)
      write_cb_();
  }
}

}  // namespace core

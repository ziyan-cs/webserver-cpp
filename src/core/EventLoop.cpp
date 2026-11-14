#include "core/EventLoop.h"

#include <cerrno>
#include <stdexcept>

#include "core/Channel.h"
#include "core/Epoll.h"

namespace core {

bool EventLoop::updateChannel(Channel* ch) {
  auto it = channels_.find(ch->fd());
  if (it == channels_.end()) {
    bool ret = epoll_->add(ch->fd(), ch->events());
    if (!ret)
      return false;
    channels_[ch->fd()] = ch;
    return true;
  }
  if (it->second != ch)
    return false;

  bool ret = epoll_->mod(ch->fd(), ch->events());
  if (!ret && errno == ENOENT)
    return ret = epoll_->add(ch->fd(), ch->events());
  return ret;
}

bool EventLoop::removeChannel(Channel* ch) {
  auto it = channels_.find(ch->fd());
  if (it == channels_.end())
    return true;
  if (it->second != ch)
    return false;

  bool ret = epoll_->del(ch->fd());
  channels_.erase(it);
  return ret;
}

void EventLoop::loop() {
  if (is_looping_)
    throw std::logic_error("EventLoop::loop() is already running");

  is_looping_ = true;
  quit_ = false;

  while (!quit_) {
    auto events = epoll_->wait();
    for (auto& ev : events) {
      int fd = ev.data.fd;
      auto it = channels_.find(fd);
      if (it != channels_.end()) {
        it->second->setRevents(ev.events);
        it->second->handleEvent();
      }
    }
  }
}

}  // namespace core

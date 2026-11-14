#pragma once

#include <cstdint>
#include <functional>
#include <sys/epoll.h>

namespace core {

class EventLoop;

// Observes events on an fd without owning it.
// The event loop must remain valid until the channel is destroyed.
class Channel {
 public:
  using EventCallback = std::function<void()>;

  static const uint32_t kReadEvent = EPOLLIN | EPOLLPRI;
  static const uint32_t kWriteEvent = EPOLLOUT;

  explicit Channel(int fd, EventLoop* loop) : fd_(fd), loop_(loop) {}
  ~Channel() { remove(); }

  // Neither copyable nor movable.
  Channel(const Channel&) = delete;
  Channel& operator=(const Channel&) = delete;
  Channel(Channel&&) = delete;
  Channel& operator=(Channel&&) = delete;

  // Set event callbacks.
  void setOnRead(EventCallback cb) { read_cb_ = std::move(cb); }
  void setOnWrite(EventCallback cb) { write_cb_ = std::move(cb); }
  void setOnClose(EventCallback cb) { close_cb_ = std::move(cb); }

  // Control which events to listen for.
  void enableReading() { events_ |= kReadEvent; }
  void enableWriting() { events_ |= kWriteEvent; }
  void disableReading() { events_ &= ~kReadEvent; }
  void disableWriting() { events_ &= ~kWriteEvent; }
  void disableAll() { events_ = 0; }

  // Sync event changes with the event loop. Returns false on failure.
  bool update();

  // Unregister from the event loop. Returns false if removal fails.
  // The destructor also calls this function and ignores the result.
  bool remove();

  // Dispatch the reported events to their callbacks.
  void handleEvent();

  void setEvents(uint32_t events) { events_ = events; }
  void setRevents(uint32_t revents) { revents_ = revents; }
  [[nodiscard]] int fd() const { return fd_; }
  [[nodiscard]] uint32_t events() const { return events_; }
  [[nodiscard]] uint32_t revents() const { return revents_; }

 private:
  EventCallback read_cb_, write_cb_, close_cb_;

  int fd_ = -1;
  EventLoop* loop_ = nullptr;
  uint32_t events_ = 0;
  uint32_t revents_ = 0;
};

}  // namespace core

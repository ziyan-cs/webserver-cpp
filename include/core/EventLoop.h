#pragma once

#include <unordered_map>

namespace core {

class Channel;

class Epoll;

// Dispatches ready events to registered channels.
// The epoll instance and registered channels must remain valid while in use.
class EventLoop {
 public:
  explicit EventLoop(Epoll* epoll) : epoll_(epoll) {}
  ~EventLoop() = default;

  // Neither copyable nor movable.
  EventLoop(const EventLoop&) = delete;
  EventLoop& operator=(const EventLoop&) = delete;
  EventLoop(EventLoop&&) = delete;
  EventLoop& operator=(EventLoop&&) = delete;

  // Manage event channels.
  bool updateChannel(Channel* ch);
  bool removeChannel(Channel* ch);

  void loop();

  // Call from the loop thread; this does not wake a blocked wait.
  void stop() noexcept { quit_ = true; }

 private:
  Epoll* epoll_ = nullptr;
  std::unordered_map<int, Channel*> channels_;
  bool is_looping_ = false;
  bool quit_ = false;
};

}  // namespace core

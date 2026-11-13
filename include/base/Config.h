#pragma once

#include <cstdint>
#include <string>

namespace base {

class Config {
 public:
  static Config& instance();

  // Neither copyable nor movable.
  Config(const Config&) = delete;
  Config& operator=(const Config&) = delete;
  Config(Config&&) = delete;
  Config& operator=(Config&&) = delete;

  [[nodiscard]] const std::string& ip() const { return ip_; }
  [[nodiscard]] uint16_t port() const { return port_; }
  [[nodiscard]] int backlog() const { return backlog_; }

 private:
  Config() = default;
  ~Config() = default;

  std::string ip_ = "0.0.0.0";
  uint16_t port_ = 8080;
  int backlog_ = 128;
};

}  // namespace base

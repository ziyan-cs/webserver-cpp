#pragma once

#include <cstdint>
#include <string>

namespace base {

class Logger {
 public:
  enum class LogLevel : uint8_t {
    DEBUG,  // 0
    INFO,   // 1
    WARN,   // 2
    ERROR   // 3
  };

  static Logger& instance();

  // Neither copyable nor movable.
  Logger(const Logger&) = delete;
  Logger& operator=(const Logger&) = delete;
  Logger(Logger&&) = delete;
  Logger& operator=(Logger&&) = delete;

  void log(LogLevel level, const std::string& msg) const;

  void setLevel(LogLevel level) { level_ = level; }
  [[nodiscard]] LogLevel level() const { return level_; }

 private:
  Logger() = default;
  ~Logger() = default;

  [[nodiscard]] std::string CurrentTimeString() const;

  inline static LogLevel level_ = LogLevel::DEBUG;
};

}  // namespace base

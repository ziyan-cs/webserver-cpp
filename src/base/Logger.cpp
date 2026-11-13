#include "base/Logger.h"

#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>

namespace base {

Logger& Logger::instance() {
  static Logger logger;
  return logger;
}

void Logger::log(LogLevel level, const std::string& msg) const {
  if (level < level_) {
    return;
  }

  int level_value = static_cast<int>(level);
  static const char* level_names[] = {"DEBUG", "INFO ", "WARN ", "ERROR"};
  std::string level_name = level_names[level_value];

  std::cout << '[' << CurrentTimeString() << "] " << '[' << level_name << "] " << msg << '\n';
}

std::string Logger::CurrentTimeString() const {
  const auto now = std::chrono::system_clock::now();
  const auto secs = std::chrono::floor<std::chrono::seconds>(now);
  const auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now - secs).count();
  const std::time_t t = std::chrono::system_clock::to_time_t(secs);

  std::tm tm_result{};
#ifdef _WIN32
  localtime_s(&tm_result, &t);
#else
  localtime_r(&t, &tm_result);
#endif

  std::ostringstream output;
  output << std::put_time(&tm_result, "%Y-%m-%d %H:%M:%S") << '.' << std::setfill('0')
         << std::setw(3) << ms;
  return output.str();
}

}  // namespace base

#include "base/Logger.h"

#include <cassert>

int main() {
  auto& logger = base::Logger::instance();

  logger.setLevel(base::Logger::LogLevel::WARN);
  assert(logger.level() == base::Logger::LogLevel::WARN);

  logger.log(base::Logger::LogLevel::DEBUG, "T");  // This line should not be printed.
  logger.log(base::Logger::LogLevel::INFO, "");    // This line should not be printed.

  logger.log(base::Logger::LogLevel::WARN, "");   // This line should be printed.
  logger.log(base::Logger::LogLevel::ERROR, "");  // This line should be printed.

  return 0;
}

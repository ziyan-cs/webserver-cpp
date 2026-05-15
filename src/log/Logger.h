// log/Logger/h
#include <iostream>

#define LOG_INFO(msg)  std::cout << "[INFO]  " << msg << '\n'
#define LOG_DEBUG(msg) std::cout << "[DEBUG] " << msg << '\n'
#define LOG_WARN(msg)  std::cout << "[WARN]  " << msg << '\n'
#define LOG_ERROR(msg) std::cout << "[ERROR] " << msg << '\n'
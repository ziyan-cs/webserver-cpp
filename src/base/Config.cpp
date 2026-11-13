#include "base/Config.h"

namespace base {

Config& Config::instance() {
  static Config config;
  return config;
}

}  // namespace base

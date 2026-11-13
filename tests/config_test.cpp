#include "base/Config.h"

int main() {
  const auto& config = base::Config::instance();

  return config.ip() == "0.0.0.0" && config.port() == 8080 && config.backlog() == 128 ? 0 : 1;
}

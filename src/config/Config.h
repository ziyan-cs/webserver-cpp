// config/Config.h
#pragma once

#include <unistd.h>

namespace webserver {

extern ssize_t BUFFER_SIZE;
extern int MAX_EVENTS;
extern int LISTEN_BACKLOG;

} // namespace webserver
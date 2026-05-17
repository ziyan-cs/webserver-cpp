// config/Config.h
#pragma once

namespace webserver {

extern size_t BUFFER_SIZE;
extern int MAX_EVENTS;
extern int LISTEN_BACKLOG;

void config(ssize_t buffer_size, int max_events, int listen_backlog);

} // namespace webserver
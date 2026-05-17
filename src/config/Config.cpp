// config/Config.cpp
#include <config/Config.h>
#include <iostream>

namespace webserver {

ssize_t BUFSIZE = 1024;
int MAX_EVENTS = 1024;
int LISTEN_BACKLOG = 128;

void config(ssize_t buffer_size, int max_events, int listen_backlog){
    BUFSIZE = buffer_size;
    MAX_EVENTS = max_events;
    LISTEN_BACKLOG = listen_backlog;
}

} // namespace webserver
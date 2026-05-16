// core/Channel.cpp
#include "core/Channel.h"

namespace webserver {

Channel::Channel(Epoll* epoll, int fd)
    : epoll_(epoll),
      fd_(fd),
      events_(0),
      is_in_epoll_(false)
{
}


Channel::~Channel() {
    // None
}

} // namespace webserver
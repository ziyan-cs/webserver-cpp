#include <unistd.h>

#include "core/Channel.h"
#include "core/Epoll.h"
#include "core/EventLoop.h"

int main() {
  core::Epoll epoll;
  core::EventLoop loop(&epoll);

  int fds[2];
  if (pipe(fds) == -1) {
    return 1;
  }

  core::Channel read_ch(fds[0], &loop);

  bool received = false;
  read_ch.setOnRead([&] {
    char buf[16]{};
    const auto n = read(fds[0], buf, sizeof(buf));
    received = (n == 11);
    loop.stop();
  });

  read_ch.enableReading();

  if (!read_ch.update()) {
    ::close(fds[0]);
    ::close(fds[1]);
    return 1;
  }

  if (write(fds[1], "hello world", 11) != 11) {
    ::close(fds[0]);
    ::close(fds[1]);
    return 1;
  }

  loop.loop();

  if (!read_ch.remove()) {
    ::close(fds[0]);
    ::close(fds[1]);
    return 1;
  }

  ::close(fds[0]);
  ::close(fds[1]);

  return received ? 0 : 1;
}

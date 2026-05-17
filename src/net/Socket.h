// net/Socket.h
#pragma once

#include <string>

namespace webserver {

class Socket {
public:
	Socket();
    Socket(int fd);
	~Socket();

    void bindSock(int port, std::string ip);
    void listenSock(int backlg);

    // Getters
    int fd() const { return fd_; }
private:
    int fd_;
};

} // namespace webserver
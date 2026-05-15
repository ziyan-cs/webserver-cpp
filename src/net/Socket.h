// net/Socket.h
#pragma once

#include <string>

namespace webserver {

class Socket {
public:
	Socket();
	~Socket();

    void bindSock(int pork, std::string ip);
    void listenSock(int backlg);
    int acceptSock();

    // Getters
    int fd() const { return fd_; }
private:
    int fd_;
};

} // namespace webserver
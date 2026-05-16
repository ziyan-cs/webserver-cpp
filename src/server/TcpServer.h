// server/TcpServer.h
#pragma once
#include "config/Config.h"
#include "net/Socket.h"

namespace webserver {

class TcpServer {
public:
    TcpServer(const Config& config);
    ~TcpServer();

    void start();
private:
    void init();
    void run();

    Config config_;
    Socket listen_socket_;
};

} // namespace webserver
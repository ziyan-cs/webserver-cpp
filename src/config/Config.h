// config/Config.h
#include <string>

namespace webserver {

class Config {
public:
    Config();
    Config(int port, int backlog, int buffer_size, std::string ip);

    // Getters
    int port() const { return port_; }
    int backlog() const { return backlog_; }
    int bufferSize() const { return buffer_size_; }\
    std::string ip() const { return ip_; }

    // Setters
    void setPort(int port) { port_ = port; }
    void setBacklog(int backlog) { backlog_ = backlog; }
    void setBufferSize(int buffer_size) { buffer_size_ = buffer_size; }
    void setIp(std::string ip) { ip_ = ip; }

    // Debug
    void print() const;
private:
    int port_;
    int backlog_;
    int buffer_size_;
    std::string ip_;
};

} // namespace webserver
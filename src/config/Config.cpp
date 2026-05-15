// config/Config.cpp
#include <config/Config.h>
#include <iostream>

namespace webserver {

Config::Config()
    : port_(8080),
      backlog_(),
      buffer_size_(),
      ip_("0.0.0.0")
{
}

Config::Config(int port, int backlog, int buffer_size, std::string ip)
    : port_(port),
      backlog_(backlog),
      buffer_size_(buffer_size),
      ip_(ip)
{
}

void Config::print() const {
    std::cout << "=====Configuration=====" << '\n';
    std::cout << "Port = " << port_ << '\n';
    std::cout << "Backlog = " << backlog_ << '\n';
    std::cout << "Buffer Size = " << buffer_size_ << '\n';
    std::cout << "Server IP = " << ip_ << '\n';
    std::cout << "=======================" << '\n';
}

}
// server/main.cpp
#include "log/Logger.h"
#include "server/TcpServer.h"
#include <iostream>

int main() {
    char choice;
    std::cout << "Whether to use default config?(y/n): ";
    std::cin >> choice;

    if (choice != 'y' && choice != 'Y') {
        int port, backlog, bufferSize;
        std::string ip;

        std::cout << "\nInput the Port: ";
        std::cin >> port;

        std::cout << "\nInput the Backlog: ";
        std::cin >> backlog;

        std::cout << "\nInput the Buffer Size: ";
        std::cin >> bufferSize;

        std::cout << "\nInput the Server IP: ";
        std::cin >> ip;

        config = webserver::Config(port, backlog, bufferSize, ip);
    } else {
        config = webserver::Config();
    }
    config.print();

    webserver::TcpServer server(config);
    server.start();

    LOG_INFO("Exiting");
    return 0;

}
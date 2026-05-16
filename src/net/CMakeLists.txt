add_library(net STATIC
    Socket.cpp
    Acceptor.cpp
    TcpConnection.cpp
    # Buffer.h
)

target_link_libraries(net PUBLIC
    core
)
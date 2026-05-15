add_library(net STATIC
    Socket.cpp
    # Acceptor.cpp
    # TcpConnection.cpp
    # Buffer.h
    # InetAddress.cpp
)

target_link_libraries(net PUBLIC
    core
)
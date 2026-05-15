add_library(net STATIC
    Socket.cpp
    # Acceptor.cpp
    # TcpConnection.cpp
    # Buffer.h
    # InetAddress.cpp
)

target_include_directories(net PUBLIC
    ${PROJECT_SOURCE_DIR}/src
)

target_link_libraries(net PUBLIC
    core
    log
)
add_library(net STATIC
    InetAddress.cpp
    Socket.cpp
    Acceptor.cpp
    TcpConnection.cpp
    TcpServer.cpp
)

target_include_directories(net PUBLIC ${PROJECT_SOURCE_DIR}/include)

target_link_libraries(net PRIVATE core base)

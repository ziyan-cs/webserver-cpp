add_executable(webserver
    main.cpp
    TcpServer.cpp
)

target_include_directories(webserver PUBLIC
    ${PROJECT_SOURCE_DIR}/src
)

target_link_libraries(webserver PUBLIC
    config
    core
    net
    http
    log
    pool
)
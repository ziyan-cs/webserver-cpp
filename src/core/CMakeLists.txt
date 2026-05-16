add_library(core STATIC
    Channel.cpp
    Epoll.cpp
    # EventLoop.cpp
    # Timer.cpp
)

target_include_directories(core PUBLIC
    ${PROJECT_SOURCE_DIR}/src
)

target_link_libraries(core PUBLIC
    log
)
add_library(core STATIC
    Channel.cpp
    Epoll.cpp
    EventLoop.cpp
)

target_include_directories(core PUBLIC ${PROJECT_SOURCE_DIR}/include)

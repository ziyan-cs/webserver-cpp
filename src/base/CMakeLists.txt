add_library(base STATIC
    Config.cpp
    Logger.cpp
    Buffer.cpp
)

target_include_directories(base PUBLIC ${PROJECT_SOURCE_DIR}/include)

add_library(config STATIC
    Config.cpp
)

target_include_directories(config PUBLIC
    ${PROJECT_SOURCE_DIR}/src
)
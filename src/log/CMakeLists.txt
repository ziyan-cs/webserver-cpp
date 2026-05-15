add_library(log STATIC
    # Logger.cpp
)

target_include_directories(log PUBLIC
    ${PROJECT_SOURCE_DIR}/src
)
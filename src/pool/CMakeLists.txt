# pool/CMakeLists.txt
add_library(pool STATIC
    # ThreadPool.cpp
)

target_include_directories(pool PUBLIC
    ${PROJECT_SOURCE_DIR}/src
)

target_link_libraries(pool PUBLIC
    log
)
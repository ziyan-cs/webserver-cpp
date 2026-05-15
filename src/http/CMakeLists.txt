add_library(http STATIC
    # HttpRequest.cpp
    # HttpResponse.cpp
    # HttpParser.cpp
)

target_include_directories(http PUBLIC
    ${PROJECT_SOURCE_DIR}/src
)

target_link_libraries(http PUBLIC
    net
    log
)
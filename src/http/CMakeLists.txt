add_library(http STATIC
    HttpRequest.cpp
    # HttpResponse.cpp
    # HttpParser.cpp
)


target_link_libraries(http PUBLIC
    net
    log
)
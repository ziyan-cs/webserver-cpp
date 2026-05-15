# CMakeLists.txt
cmake_minimum_required(VERSION 3.16)

project(WebServer VERSION 0.0.0)

# C++ 标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 编译选项
set(CMAKE_CXX_FLAGS
    "${CMAKE_CXX_FLAGS} -Wall -Wextra -g"
)

# 输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY
    ${PROJECT_SOURCE_DIR}/bin
)

# 添加子目录
add_subdirectory(src)

# 测试
# add_subdirectory(test)
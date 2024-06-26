cmake_minimum_required(VERSION 3.5)
project(ConsistentHashExample)

# 设置C++标准
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 设置头文件路径
include_directories(${CMAKE_SOURCE_DIR}/include)

# 获取源文件列表
file(GLOB SOURCES ${CMAKE_SOURCE_DIR}/src/*.cpp)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

# 生成可执行文件
add_executable(consistent_hash_example ${SOURCES})
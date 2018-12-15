cmake_minimum_required(VERSION 3.9)
project(neural-network)

set(CMAKE_CXX_STANDARD 11)

add_executable(network main.cpp src/support.cpp src/Model.cpp src/Png.cpp)

find_package(PNG REQUIRED)
include_directories(${PNG_INCLUDE_DIR})

target_link_libraries(network ${PNG_LIBRARY})
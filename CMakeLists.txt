cmake_minimum_required(VERSION 3.9)
project(neural-network)

set(CMAKE_CXX_STANDARD 11)

add_library(image src/image.h src/image.cpp)
add_library(matrix src/matrix.h src/matrix.cpp)
add_library(network src/network.h src/network.cpp)

add_executable(app.out main.cpp)

find_package(PNG REQUIRED)
include_directories(${PNG_INCLUDE_DIR})

target_link_libraries(app.out image matrix network ${PNG_LIBRARY} )

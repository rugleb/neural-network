cmake_minimum_required(VERSION 3.9)
project(neural-network)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(src)
add_executable(nn main.cpp)

add_subdirectory(lib)

target_link_libraries(nn libimage libmatrix libnetwork)

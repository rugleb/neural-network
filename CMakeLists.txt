cmake_minimum_required(VERSION 3.9)
project(neural-network)

set(CMAKE_CXX_STANDARD 11)

add_library(image src/image.h src/image.cpp)
add_library(matrix src/matrix.h src/matrix.cpp)
add_library(network src/network.h src/network.cpp)

add_executable(app.out main.cpp)

include_directories (${LIBPNG_INCLUDE_DIRS})
link_directories (${LIBPNG_LIBRARY_DIRS})
link_libraries (${LIBPNG_LIBRARIES})

target_link_libraries(app.out image matrix network ${LIBPNG_LINK_FLAGS})

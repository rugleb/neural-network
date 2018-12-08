cmake_minimum_required(VERSION 3.9)
project(neural-network)

set(CMAKE_CXX_STANDARD 11)

add_executable(network main.cpp src/Model.cpp src/Model.h src/Layer.cpp src/Layer.h src/support/math.cpp src/support/math.h)

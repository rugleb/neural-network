cmake_minimum_required(VERSION 3.9)
project(neural-network)

set(CMAKE_CXX_STANDARD 14)

add_executable(network main.cpp src/model.cpp src/model.h src/support.cpp src/support.h src/layer.cpp src/layer.h)
cmake_minimum_required(VERSION 3.9)
project(neural-network)

set(CMAKE_CXX_STANDARD 11)

add_executable(network main.cpp src/Model.cpp src/Model.h src/Layer.cpp src/Layer.h src/Matrix.cpp src/Matrix.h)

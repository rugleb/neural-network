cmake_minimum_required(VERSION 3.9)
project(nn_cpp)

set(CMAKE_CXX_STANDARD 14)

add_executable(nn_cpp main.cpp src/model.cpp src/model.h)
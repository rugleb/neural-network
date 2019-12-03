cmake_minimum_required(VERSION 3.1)
project(libnetwork)

set(CMAKE_CXX_STANDARD 17)

set(LIBRARY_NAME ${PROJECT_NAME})
set(LIBRARY_TYPE STATIC)

file(GLOB SOURCES src/*.cpp)
file(GLOB HEADERS include/*.hpp)

find_library(libmatrix REQUIRED)

add_library(${LIBRARY_NAME} ${LIBRARY_TYPE} ${SOURCES} ${HEADERS})

target_link_libraries(${LIBRARY_NAME} libmatrix)

target_include_directories(${LIBRARY_NAME}
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_compile_options(${LIBRARY_NAME} PRIVATE -Werror)

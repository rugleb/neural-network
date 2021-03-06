cmake_minimum_required(VERSION 3.10)
project(libimage)

set(CMAKE_CXX_STANDARD 17)

set(LIBRARY_NAME ${PROJECT_NAME})
set(LIBRARY_TYPE)

file(GLOB SOURCES src/*.cpp)
file(GLOB HEADERS include/*.hpp)

find_package(PNG REQUIRED)
include_directories(${PNG_INCLUDE_DIR})

find_library(libmatrix REQUIRED)
find_library(libnetwork REQUIRED)

add_library(${LIBRARY_NAME} ${LIBRARY_TYPE} ${SOURCES} ${HEADERS})

target_link_libraries(${LIBRARY_NAME} ${PNG_LIBRARY})
target_link_libraries(${LIBRARY_NAME} libmatrix)
target_link_libraries(${LIBRARY_NAME} libnetwork)

target_include_directories(${LIBRARY_NAME}
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_compile_options(${LIBRARY_NAME} PRIVATE -Werror)

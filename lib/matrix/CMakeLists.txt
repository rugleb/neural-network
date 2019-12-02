cmake_minimum_required(VERSION 3.10)
project(Matrix)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_OUTPUT_EXTENSION_REPLACE 1)
set(CMAKE_CXX_EXTENSIONS 0)

set(SOURCES
    src/Matrix.cpp
    src/Operator.cpp
    src/Utils.cpp
)

set(HEADERS
    include/Matrix/Matrix.hpp
    include/Matrix/Operator.hpp
    include/Matrix/Utils.hpp
)

add_library(${PROJECT_NAME} ${SOURCES} ${HEADERS})

target_include_directories(${PROJECT_NAME}
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

set_target_properties(${PROJECT_NAME}
    PROPERTIES
        PREFIX ""
        OUTPUT_NAME ${PROJECT_NAME}
)

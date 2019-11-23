cmake_minimum_required(VERSION 3.10)
project(TestMatrix)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_OUTPUT_EXTENSION_REPLACE 1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")

set(SOURCES
    main.cpp
    TestUtils.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

find_package(GTest REQUIRED)
find_library(Matrix REQUIRED)
find_package(Threads REQUIRED)

include_directories(${GTEST_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME} ${GTEST_LIBRARIES} Matrix pthread)

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

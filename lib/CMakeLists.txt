cmake_minimum_required(VERSION 3.1)

add_subdirectory(matrix)

option(TESTS_ENABLED "Build the tests" ON)

if (TESTS_ENABLED)
    enable_testing()
    add_subdirectory(tests)
endif ()

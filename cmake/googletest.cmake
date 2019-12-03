set(GTEST_DIR ${PROJECT_BINARY_DIR}/contrib/googletest)

configure_file(
    ${PROJECT_SOURCE_DIR}/cmake/googletest-download.cmake
    ${GTEST_DIR}/CMakeLists.txt
)

execute_process(
    COMMAND
        "${CMAKE_COMMAND}" -G "${CMAKE_GENERATOR}" .
    WORKING_DIRECTORY
        ${GTEST_DIR}
    RESULT_VARIABLE
        result
)

if (result)
    message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()

execute_process(
    COMMAND
        "${CMAKE_COMMAND}" --build .
    WORKING_DIRECTORY
        ${GTEST_DIR}
    RESULT_VARIABLE
        result
)

if (result)
    message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()

add_subdirectory(
    ${GTEST_DIR}/googletest-src
    ${GTEST_DIR}/googletest-build
    EXCLUDE_FROM_ALL
)

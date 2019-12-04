set(LIBPNG_DIR ${PROJECT_BINARY_DIR}/contrib/libpng)

configure_file(
    ${PROJECT_SOURCE_DIR}/cmake/libpng-download.cmake
    ${LIBPNG_DIR}/CMakeLists.txt
)

execute_process(
    COMMAND
        "${CMAKE_COMMAND}" -G "${CMAKE_GENERATOR}" .
    WORKING_DIRECTORY
        ${LIBPNG_DIR}
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
        ${LIBPNG_DIR}
    RESULT_VARIABLE
        result
)

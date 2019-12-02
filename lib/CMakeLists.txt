add_subdirectory(matrix)

option(TESTS_ENABLED "Build the tests" ON)

if (TESTS_ENABLED)

    include(ExternalProject)
    ExternalProject_Add(gtest
        URL https://github.com/google/googletest/archive/release-1.8.0.zip
        PREFIX ${CMAKE_CURRENT_BINARY_DIR}/gtest
        INSTALL_COMMAND ""
    )
    ExternalProject_Get_Property(gtest source_dir binary_dir)

    enable_testing()
    add_subdirectory(tests)

endif ()

cmake_minimum_required(VERSION 3.5)

project(googletest NONE)

include(ExternalProject)

ExternalProject_Add(googletest
    SOURCE_DIR        "@GTEST_DIR@/googletest-src"
    BINARY_DIR        "@GTEST_DIR@/googletest-build"
    GIT_REPOSITORY    https://github.com/google/googletest.git
    GIT_TAG           release-1.8.0
    CONFIGURE_COMMAND ""
    BUILD_COMMAND     ""
    INSTALL_COMMAND   ""
    TEST_COMMAND      ""
)

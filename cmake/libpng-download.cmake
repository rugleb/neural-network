cmake_minimum_required(VERSION 3.5)

project(libpng NONE)

include(ExternalProject)

ExternalProject_Add(zlib
    GIT_REPOSITORY    https://github.com/madler/zlib.git
    GIT_TAG           v1.2.11
    CONFIGURE_COMMAND ""
    BUILD_COMMAND     ""
    INSTALL_COMMAND   ""
    TEST_COMMAND      ""
)

ExternalProject_Add(libpng
    GIT_REPOSITORY    https://github.com/glennrp/libpng.git
    GIT_TAG           v1.5.29
    CONFIGURE_COMMAND ""
    BUILD_COMMAND     ""
    INSTALL_COMMAND   ""
    TEST_COMMAND      ""
    DEPENDS           zlib
)

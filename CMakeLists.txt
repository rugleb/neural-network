cmake_minimum_required(VERSION 3.9)
project(neural-network)

set(CMAKE_CXX_STANDARD 17)

include(GNUInstallDirs)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR})

add_subdirectory(cmake)
add_subdirectory(src)
add_subdirectory(lib)

add_executable(nn main.cpp)

target_link_libraries(nn libimage libmatrix libnetwork)

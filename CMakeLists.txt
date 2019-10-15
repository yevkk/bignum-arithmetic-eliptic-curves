cmake_minimum_required(VERSION 3.15)
project(bignum_arithmetic_eliptic_curves)

set(CMAKE_CXX_STANDARD 17)

set(TOP_DIR ${CMAKE_SOURCE_DIR})

# set up output directories
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

option(ENABLE_TESTS "Build tests for project" ON)
if (ENABLE_TESTS)
  add_subdirectory(${TOP_DIR}/Tests)
endif()


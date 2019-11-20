cmake_minimum_required(VERSION 3.15)
project(lab)

# whole project uses C++17
set(CMAKE_CXX_STANDARD 17)

set(TOP_DIR ${CMAKE_SOURCE_DIR})
set(SRC_DIR ${TOP_DIR}/Src)

# make these files available for all project
include_directories(${SRC_DIR})

# set up output directories
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(SRC_LIST
    ${SRC_DIR}/EllipticCurves.cpp
    ${SRC_DIR}/BigNum.cpp
    ${SRC_DIR}/Multiplication.cpp
)

set(LIBRARY_NAME ${PROJECT_NAME}core)

add_library(${LIBRARY_NAME} STATIC ${SRC_LIST})

option(ENABLE_TESTS "Build tests for project" ON)
if (ENABLE_TESTS)
  add_subdirectory(${TOP_DIR}/Tests)
endif()

# tmp executable for quick testing
add_executable(main main.cpp)
target_link_libraries(main PRIVATE ${LIBRARY_NAME})

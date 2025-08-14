cmake_minimum_required(VERSION 3.0)
project(scribe)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_BUILD_TYPE Debug)

include(CTest)
set(CTEST_OUTPUT_ON_FAILURE TRUE)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)
add_subdirectory(src)

add_subdirectory(tests)



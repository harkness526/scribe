cmake_minimum_required(VERSION 3.0)
project(scribe)

include(CTest)

add_subdirectory(src)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)
add_subdirectory(tests)



cmake_minimum_required(VERSION 3.0)
project(scribe)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_BUILD_TYPE Debug)

find_package(GTest REQUIRED)

include(CTest)
include(GoogleTest)


set(CTEST_OUTPUT_ON_FAILURE TRUE)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)
add_subdirectory(src)

add_subdirectory(tests)

add_executable(unit_tests ${UNIT_TESTS_SRC})
target_link_libraries(unit_tests ${UNIT_TESTS_LIBS} GTest::GTest GTest::Main)
gtest_discover_tests(unit_tests)

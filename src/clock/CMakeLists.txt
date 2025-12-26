add_library(clock OBJECT adding_clock/AddingClock.cc)
target_include_directories(clock PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

file(GLOB CLOCK_TESTS_SRC tests/*.cc )
set(UNIT_TESTS_SRC ${UNIT_TESTS_SRC} ${CLOCK_TESTS_SRC} PARENT_SCOPE)
set(UNIT_TESTS_LIBS ${UNIT_TESTS_LIBS} clock PARENT_SCOPE)

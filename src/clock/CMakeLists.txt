add_library(clock OBJECT adding_clock/AddingClock.cc)
target_include_directories(clock PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(tests)


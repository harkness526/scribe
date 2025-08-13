file(GLOB TEST_SRC_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cc )

create_test_sourcelist (Tests ClockTestDriver.cc ${TEST_SRC_FILES})

add_executable (ClockTestDriver ${Tests})
target_link_libraries(ClockTestDriver PUBLIC clock)

foreach (test ${TEST_SRC_FILES})
  get_filename_component (TName ${test} NAME_WE)
  add_test (NAME ${TName} COMMAND ClockTestDriver ${TName})
endforeach ()


file(GLOB TEST_SRC_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cc )

create_test_sourcelist (Tests buildertd.cc ${TEST_SRC_FILES})

add_executable (buildertd ${Tests})
target_link_libraries(buildertd PUBLIC builder)

foreach (test ${TEST_SRC_FILES})
  get_filename_component (TName ${test} NAME_WE)
  add_test (NAME ${TName} COMMAND buildertd ${TName})
endforeach ()



add_subdirectory(clock)
add_subdirectory(builder)
add_subdirectory(writer)
add_subdirectory(logger)
add_subdirectory(factory)

add_library(scribe STATIC builder writer logger factory)
set_target_properties(scribe PROPERTIES LINKER_LANGUAGE CXX)

set(UNIT_TESTS_SRC ${UNIT_TESTS_SRC} PARENT_SCOPE)
set(UNIT_TESTS_LIBS ${UNIT_TESTS_LIBS} PARENT_SCOPE)

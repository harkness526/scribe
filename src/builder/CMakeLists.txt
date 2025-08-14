file(GLOB PLANE_BUILDER_SRC plane/*.cc )
file(GLOB FORMATTED_BUILDER_SRC fmt_bulder/*.cc )

add_library(builder OBJECT ${PLANE_BUILDER_SRC} ${FORMATTED_BUILDER_SRC})
target_include_directories(builder PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(tests)

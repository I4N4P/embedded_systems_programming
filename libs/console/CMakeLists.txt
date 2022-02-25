add_library(console console.c console.h)

target_include_directories(console PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(console striing)
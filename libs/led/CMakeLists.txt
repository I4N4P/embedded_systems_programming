add_library(led led.c led.h)

target_include_directories(led PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_library(keyboard keyboard.c keyboard.h)

target_include_directories(keyboard PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

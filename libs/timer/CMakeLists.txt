add_library(timer timer.c timer.h)

target_include_directories(timer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

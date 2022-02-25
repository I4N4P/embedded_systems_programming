add_library(servo servo.c servo.h)

target_include_directories(servo PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(servo led)
target_link_libraries(servo timer_it)

add_library(uart uart.c uart.h)

target_include_directories(uart PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(uart led)


cmake_minimum_required(VERSION 2.8.3)
project(uart)

include_directories(sources/include ../deps/rs232)

set(serial_SRCS ../deps/rs232/rs232.h ../deps/rs232/rs232.c ./source/include/UART.hpp ./source/src/UART.cpp)

## Add serial library
add_library(rs232 ${serial_SRCS})

SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=gnu++11 -pthread -Wall -Wextra -o2" )

## Build your executable
add_executable(test_uart tests/main.cpp)
## Link your executable against the library
target_link_libraries(test_uart rs232)

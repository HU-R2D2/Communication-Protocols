cmake_minimum_required(VERSION 2.8.3)
project(uart)

include_directories(sources/include ../deps/serial-master/include)

set(serial_SRCS ../deps/serial-master/src/serial.cc ../deps/serial-master/include/serial/serial.h ../deps/serial-master/include/serial/v8stdint.h)
if(UNIX)
    list(APPEND serial_SRCS ../deps/serial-master/src/impl/unix.cc)
else()
    list(APPEND serial_SRCS ../deps/serial-master/src/impl/win.cc)
endif()

## Add serial library
add_library(serial ${serial_SRCS})
if(UNIX AND NOT APPLE)
    target_link_libraries(serial rt)
endif()

SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=c++11" )

## Build your executable
add_executable(test_uart source/src/UART.cpp)
## Link your executable against the library
target_link_libraries(test_uart serial)
cmake_minimum_required(VERSION 2.8.3)
project(communication-protocols)

include_directories(include)

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

## Build your executable
add_executable(my_program src/my_program.cpp)
## Link your executable against the library
target_link_libraries(my_program serial)
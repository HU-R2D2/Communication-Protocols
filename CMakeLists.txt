cmake_minimum_required(VERSION 2.8.3)
project(TCPSocket)

include_directories(../deps/practicalSocket)

set(serial_SRCS 
../deps/practicalSocket/PracticalSocket.h 
../deps/practicalSocket/PracticalSocket.cpp
./source/include/TCP_Linux.hpp
./source/src/TCP_Linux.cpp)

## Add serial library
add_library(practical ${serial_SRCS})

SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=gnu++11 -pthread" )

## Build your executable
add_executable(test_socket tests/main.cpp)
## Link your executable against the library
target_link_libraries(test_socket practical)

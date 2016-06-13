cmake_minimum_required(VERSION 2.8.9)
project( uart )
find_package (Threads)

file(GLOB SOURCES "source/src/*.cpp" "source/include/*.hpp")

include_directories(
  sources/include
  ../deps/rs232
)


SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=gnu++0x -pthread -Wall -Wextra -o2" )
set(serial_SRCS ../deps/rs232/rs232.h ../deps/rs232/rs232.c ./source/include/UART.hpp ./source/src/UART.cpp)
add_library(rs232 ${serial_SRCS})


add_executable(uart ${SOURCES})

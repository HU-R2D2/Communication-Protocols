cmake_minimum_required(VERSION 2.8.9)
project(ComminucationProtocols)
find_package (Threads)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++0x -W -O3 -lpthread -Wsign-compare -Wextra -pedantic -lssl -lcrypto -pthread ")



file(GLOB SOURCES "source/src/*.cpp" "source/src/json/*.cpp" )
file(GLOB SOURCES_GTEST "source/src/*.cpp" "source/src/json/*.cpp" "test/*.cpp")

include_directories(
  ../deps/gtest-1.7.0/include
  ../deps/gtest-1.7.0
  sources/include ../deps/rs232
  )

SET(serial_SRCS ../deps/rs232/rs232.h ../deps/rs232/rs232.c ./source/include/UART.hpp ./source/src/UART.cpp)

link_directories(../deps/gtest-1.7.0/src)
ADD_LIBRARY(gtest ../deps/gtest-1.7.0/src/gtest-all.cc)
ADD_LIBRARY(rs232 ${serial_SRCS})
ADD_LIBRARY(gtest_main ../deps/gtest-1.7.0/src/gtest_main.cc)


add_executable(ComminucationProtocols_test  ${GTEST} ${SOURCES_GTEST}  ${SOURCES})
##add_executable(test_uart tests/main.cpp)
target_link_libraries(ComminucationProtocols_test  gtest gtest_main ${CMAKE_THREAD_LIBS_INIT} ${SOURCES} "-Wl,--allow-multiple-definition")


## Link your executable against the library
##/target_link_libraries(test_uart rs232)

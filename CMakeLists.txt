cmake_minimum_required(VERSION 2.8.9)
project(ComminucationProtocols)
find_package (Threads)
find_library(ws2_32_LIBRARY_PATH ws2_32)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lws2_32")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++0x -lpthread -lssl -lcrypto -pthread -D_WINSOCK_H ")

set(serial_SRCS ../deps/rs232/rs232.h ../deps/rs232/rs232.c ./source/include/UART.hpp ./source/src/UART.cpp)


file(GLOB SOURCES "source/src/*.cpp" "source/src/json/*.cpp"  )
file(GLOB SOURCES_GTEST "source/src/*.cpp" "source/src/json/*.cpp" "test/*.cpp" )

include_directories(
  ../deps/gtest-1.7.0/include
  ../deps/gtest-1.7.0
  ../deps/rs232
  )



link_directories(../deps/gtest-1.7.0/src)
add_library(gtest ../deps/gtest-1.7.0/src/gtest-all.cc)
add_library(rs232 ${serial_SRCS})
add_library(gtest_main ../deps/gtest-1.7.0/src/gtest_main.cc)

add_executable(ComminucationProtocols  ${SOURCES} ${SOURCES_GTEST}  ${GTEST} )
target_link_libraries(ComminucationProtocols gtest rs232 gtest_main ${ws2_32_LIBRARY_PATH} ${CMAKE_THREAD_LIBS_INIT} ${SOURCES}  "-Wl,--allow-multiple-definition" )

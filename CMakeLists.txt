cmake_minimum_required(VERSION 2.8.9)
project(ComminucationProtocols)
find_package (Threads)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11 -O2 -lpthread -lssl -lcrypto -pthread ")
set(serial_SRCS ../deps/rs232/rs232.h ../deps/rs232/rs232.c ./source/include/UART.hpp ./source/src/UART.cpp)
set(BASEPATH "${CMAKE_SOURCE_DIR}")
include_directories("${BASEPATH}")


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


add_executable(ComminucationProtocols_test  ${GTEST} ${SOURCES_GTEST}  ${SOURCES})
target_link_libraries(ComminucationProtocols_test gtest rs232 gtest_main ${CMAKE_THREAD_LIBS_INIT} ${SOURCES} "-Wl,--allow-multiple-definition")

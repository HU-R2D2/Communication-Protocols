cmake_minimum_required(VERSION 2.8.9)
project(ComminucationProtocols)
find_package (Threads)
find_library(ws2_32_LIBRARY_PATH ws2_32)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lws2_32")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++0x -lpthread -lssl -lcrypto -pthread -D_WINSOCK_H ")

set(serial_SRCS ../deps/rs232/rs232.h ../deps/rs232/rs232.c ./source/include/UART.hpp ./source/src/UART.cpp)
set(rest_SRCS ../deps/REST/include/RESTCallBack.hpp
../deps/REST/include/RESTEngine.hpp
../deps/REST/include/RESTParameters.hpp
../deps/REST/include/json/JSON.hpp
../deps/REST/include/json/List.hpp
../deps/REST/include/json/Object.hpp
../deps/REST/include/json/Parser.hpp
../deps/REST/include/json/Value.hpp
../deps/REST/src/json/JSON.cpp
../deps/REST/src/json/List.cpp
../deps/REST/src/json/Object.cpp
../deps/REST/src/json/Parser.cpp
../deps/REST/src/json/Value.cpp
../deps/REST/src/RESTCallBack.cpp
../deps/REST/src/RESTParameters.cpp
../deps/REST/src/RESTEngine.cpp
./source/include/RestApplicationProtocol.hpp
./source/src/RestApplicationProtocol.cpp
)


file(GLOB SOURCES "source/src/*.cpp" "source/src/json/*.cpp"  )
file(GLOB SOURCES_GTEST "source/src/*.cpp" "source/src/json/*.cpp" "test/*.cpp" )

include_directories(
  ../deps/gtest-1.7.0/include
  ../deps/gtest-1.7.0
  ../deps/rs232
  ../deps/REST/include
  ../deps/REST/include/json
  ../deps/REST/src/json
  ../deps/REST/src
  )



link_directories(../deps/gtest-1.7.0/src)
add_library(gtest ../deps/gtest-1.7.0/src/gtest-all.cc)
add_library(rs232 ${serial_SRCS})
add_library(rest ${rest_SRCS})
add_library(gtest_main ../deps/gtest-1.7.0/src/gtest_main.cc)

add_executable(ComminucationProtocols  ${SOURCES} ${SOURCES_GTEST}  ${GTEST} )
target_link_libraries(ComminucationProtocols gtest rest rs232 gtest_main ${ws2_32_LIBRARY_PATH} ${CMAKE_THREAD_LIBS_INIT} ${SOURCES} "-Wl,--allow-multiple-definition" ) #

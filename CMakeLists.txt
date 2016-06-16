cmake_minimum_required(VERSION 2.8.9)
project( communication_protocols )

find_library(ws2_32_LIBRARY_PATH ws2_32)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11 -pthread -Wall")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lws2_32")
file(GLOB SOURCES "source/src/*.cpp" "source/include/*.hpp")

add_executable(comp ${SOURCES})
target_link_libraries(comp ${ws2_32_LIBRARY_PATH})

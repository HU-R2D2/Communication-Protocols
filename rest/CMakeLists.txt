cmake_minimum_required(VERSION 2.8.9)
project(REST)
find_package (Threads)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mcmodel=medium -std=gnu++0x -W -O3 -lpthread -Wsign-compare -Wextra -pedantic -lssl -lcrypto -pthread ")



file(GLOB SOURCES "source/src/*.cpp" "source/src/json/*.cpp" )




add_executable(rest_test  ${SOURCES})
target_link_libraries(rest_test  ${SOURCES} "-Wl,--allow-multiple-definition")

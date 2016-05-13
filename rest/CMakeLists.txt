cmake_minimum_required(VERSION 2.8.9)
project(REST)
find_package (Threads)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mcmodel=medium -std=gnu++0x -W -O3 -lpthread -Wextra -pedantic -lssl -lcrypto -pthread ")



file(GLOB SOURCES "source/sources/*.cpp" "source/sources/json/*.cpp")




add_executable(rest_test  ${SOURCES})
target_link_libraries(rest_test  ${SOURCES} "-Wl,--allow-multiple-definition")

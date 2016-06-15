
cmake_minimum_required(VERSION 2.8.9)
project(ComminucationProtocols)
find_package (Threads)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++0x -O2 -lpthread -pthread ")
SET(BASEPATH "${CMAKE_SOURCE_DIR}")
INCLUDE_DIRECTORIES("${BASEPATH}")


file(GLOB SOURCES "source/src/*.cpp" "source/src/json/*.cpp" "source/include/json/*.hpp" "source/include/*.hpp" )
file(GLOB SOURCES_GTEST "source/src/*.cpp" "source/src/json/*.cpp" "test/*.cpp" "source/include/json/*.hpp" "source/include/*.hpp" )

include_directories(
  "../deps/gtest-1.7.0/include"
  "../deps/gtest-1.7.0"
  "../deps/rs232/"
  )

file(GLOB SOURCES "source/src/*.cpp" "source/src/json/*.cpp"  )
file(GLOB SOURCES_GTEST "source/src/*.cpp" "source/src/json/*.cpp" "test/*.cpp" )




link_directories(../deps/gtest-1.7.0/src)
add_library(gtest ../deps/gtest-1.7.0/src/gtest-all.cc)
add_library(gtest_main ../deps/gtest-1.7.0/src/gtest_main.cc)
link_directories(../deps/gtest-1.7.0/src)
link_directories(../deps/rs232/)
ADD_LIBRARY(rs232 ../deps/rs232/rs232.c)

add_executable(ComminucationProtocols_test  ${GTEST} ${SOURCES_GTEST}  ${SOURCES} ${RS232} )
target_link_libraries(ComminucationProtocols_test gtest rs232 gtest_main ${CMAKE_THREAD_LIBS_INIT} ${SOURCES} "-Wl,--allow-multiple-definition")

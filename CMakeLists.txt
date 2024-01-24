cmake_minimum_required(VERSION 3.9.1)
project(rvm)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -L./src/lib/headers -lrvmlib")

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH  ${CMAKE_BINARY_DIR}/lib)

file(GLOB_RECURSE RVM_SOURCES "./src/cli/*.c")
file(GLOB_RECURSE RVM_LIB_SOURCES "./src/lib/*.c")

add_executable(rvm ${RVM_SOURCES})

add_library(lib STATIC ${RVM_LIB_SOURCES})

target_link_libraries(rvm lib)

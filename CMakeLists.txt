cmake_minimum_required(VERSION 3.9.1)
project(rvm)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH  ${CMAKE_BINARY_DIR}/lib)

add_executable(rvm_cli src/cli/main.c)

add_library(rvm_lib STATIC src/lib/stack.c
        src/lib/buffer.c
        src/lib/headers/buffer.h
        src/lib/vm.c
        src/lib/headers/vm.h)

add_library(rvm_assembler STATIC src/assembler/translator.c
        src/assembler/headers/translator.h)

set_target_properties(rvm_cli PROPERTIES OUTPUT_NAME "rvm")
set_target_properties(rvm_lib PROPERTIES OUTPUT_NAME "rvm")

target_include_directories(rvm_lib PUBLIC src/lib/headers src/assembler/headers)

target_link_libraries(rvm_cli rvm_lib rvm_assembler)

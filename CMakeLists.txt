cmake_minimum_required(VERSION 3.9.1)
project(rvm)

set(CMAKE_C_STANDARD 23) # Use C version 23
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall") # Compile with warnings

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin) # All executable files go in cmake-build-debug/bin
set(LIBRARY_OUTPUT_PATH  ${CMAKE_BINARY_DIR}/lib) # All executable files go in cmake-build-debug/lib

add_executable(rvm_cli src/rvmcli/main.c) # Compile an executable called rvm_cli using main.c

add_library(rvm_lib STATIC  # Compile a static library called rvm_lib using ...
        src/librvm/vm.c
        src/librvm/headers/vm.h
        src/librvm/headers/instruction.h
)

add_library(rvm_assembler STATIC src/ras/ras.c # Compile a static library called rvm_lib using ...
        src/ras/headers/ras.h)

set_target_properties(rvm_cli PROPERTIES OUTPUT_NAME "rvm") # Set the output name to "rvm"
set_target_properties(rvm_lib PROPERTIES OUTPUT_NAME "rvm") # Set the output name to "rvm"

target_include_directories(rvm_lib PUBLIC src/librvm/headers src/ras/headers)  # Include the header files when building the library

target_link_libraries(rvm_cli rvm_lib rvm_assembler) # Link the rvm_cli executable with rvm_lib and rvm_assembler

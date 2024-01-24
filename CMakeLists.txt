cmake_minimum_required(VERSION 3.9.1)
project(rvm)

set(CMAKE_CXX_FLAGS "-Wall")

add_executable(rvm src/cli/main.c)

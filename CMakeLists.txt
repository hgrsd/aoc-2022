cmake_minimum_required(VERSION 3.22)
project(aoc_2022 C)

set(CMAKE_C_STANDARD 17)
#set(CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS} -Wall -fsanitize=address -fsanitize=undefined -g -O0")
set(CMAKE_EXPORT_COMPILE_COMMANDS  1)
add_subdirectory(shared)
add_subdirectory(days)

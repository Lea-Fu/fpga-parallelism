cmake_minimum_required(VERSION 3.11)
project(fpga-parallelism)

set(CMAKE_CXX_STANDARD 17)
include_directories(include)
add_executable(fpga-parallelism
        src/main.cpp
        src/sort.hpp
        src/sort_types.hpp
        src/sort.cpp)
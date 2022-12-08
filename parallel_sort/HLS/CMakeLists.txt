cmake_minimum_required(VERSION 3.11)
project(fpga-parallelism)

# added -fopenmp
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O3 -fopenmp")
#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,--stack,100000000") #needed to make the stack bigger, so that we can test sorting with more elements to test paralleling with OpenMP
# "-stack_size" --> needed for MacOs "--stack" needed for Windows

set(CMAKE_CXX_STANDARD 17)
include_directories(include)
add_executable(fpga-parallelism
        src/main.cpp
        src/sort.hpp
        src/sort2.hpp
        src/sort_types.hpp
        src/sort.cpp
        src/sort2.cpp)

enable_testing()
add_test(NAME SortTest COMMAND fpga-parallelism)
cmake_minimum_required(VERSION 3.23)
project(Rumspielen)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0 -Wall -std=c++11 -fopenmp")
set(CMAKE_CXX_STANDARD 14)

include_directories(include)
add_executable(Rumspielen main.cpp)

cmake_minimum_required(VERSION 3.11)
project(fpga_parallelism_opencl)

set(CMAKE_CXX_STANDARD 17)
include_directories(include)
add_executable(fpga-parallelism_opencl
        src/main.cpp
        )

#added -framework OpenCL
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -framework OpenCL")

set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/")
find_package( OpenCL REQUIRED )
include_directories( ${OpenCL_INCLUDE_DIR} )
include_directories( ${OpenCL_LIBRARY} )
project(HeapSort)
cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -std=c++11")

include_directories(src include)

set(SOURCE_FILES
        src/main.cpp
        include/binary_heap.hpp
)

add_executable(HeapSort ${SOURCE_FILES})

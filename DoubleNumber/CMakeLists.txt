project(DoubleNumber)
cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -O2 -std=c++11")

include_directories(src include)
set(SOURCE_FILES
    src/main.cpp
    src/double_number.cpp
    include/double_number.hpp
)

add_executable(DoubleNumber ${SOURCE_FILES})


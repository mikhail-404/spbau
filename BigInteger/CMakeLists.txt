project(BigIntegerLast)
cmake_minimum_required(VERSION 2.8)
aux_source_directory(. SRC_LIST)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(src include)

set(SOURCE_FILES
        src/main.cpp
        src/lint.cpp
        src/long_array.cpp
        include/lint.hpp
        include/long_array.hpp
)

add_executable(BigIntegerLast ${SOURCE_FILES})

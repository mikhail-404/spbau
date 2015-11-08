project(BigInteger)
cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -O2 -std=c++11")

include_directories(src include)

set(SOURCE_FILES
        src/main.cpp
        src/lint.cpp
        src/long_array.cpp
        include/lint.hpp
        include/long_array.hpp
)

add_executable(BigInteger ${SOURCE_FILES})

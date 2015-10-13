cmake_minimum_required(VERSION 2.8)
project(huffman_code)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -O2 -std=c++11")

include_directories(src include)

set(SOURCE_FILES
        src/main.cpp
        src/HuffmanCode.cpp
        src/BitsOperation.cpp
        src/TreeNode.cpp)

add_executable(huffman_code ${SOURCE_FILES})

find_package(Boost COMPONENTS program_options REQUIRED)

target_link_libraries(huffman_code ${Boost_PROGRAM_OPTIONS_LIBRARY})

include_directories(${Boost_INCLUDE_DIRS})
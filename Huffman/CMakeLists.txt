cmake_minimum_required (VERSION 2.8)

project (au_huffman)

set (CMAKE_CXX_FLAGS "-Wall -Werror -std=c++11 -g")

include_directories(src include)

set (SOURCE
    src/huffman_tree.cpp
    src/main.cpp
    src/tree_node.cpp
    src/bits_operations.cpp
    src/binary_writer.cpp
    src/binary_reader.cpp
)

add_executable(au_huffman ${SOURCE})

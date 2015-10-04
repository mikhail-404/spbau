cmake_minimum_required (VERSION 2.8)

project (au_huffman)

set (CMAKE_CXX_FLAGS "-Wall -Werror -std=c++11")

include_directories(src include)

set (SOURCE
    src/huffman_tree.cpp
    src/main.cpp
    src/tree_node.cpp
)

add_executable(au_huffman ${SOURCE})

#include <iostream>
#include <fstream>
#include <string>

#include "../include/huffman_tree.hpp"
#include <map>

int main(int argc, char *argv[])
{
    std::string source_string(argv[1]);
    std::map <char, int> dictionary;
    for(size_t i = 0; i < source_string.length(); ++i)
        ++dictionary[source_string[i]];

    HuffmanTree tree(dictionary);
    tree.codes();

    return 0;
}

//
// Created by mikhail on 10/13/15.
//

#ifndef HUFFMAN_CODE_HUFFMANCODE_HPP
#define HUFFMAN_CODE_HUFFMANCODE_HPP

#include <string>
#include <fstream>
#include <queue>

#include "TreeNode.hpp"
#include "BitsOperation.hpp"
#include "HuffmanCodeException.hpp"

class HuffmanCode
{
public:
    enum Mode { ENCODE, DECODE };

    HuffmanCode(const std::string &, const std::string &);

    void encode();
    void decode();

private:
    std::string m_input_file;
    std::string m_output_file;

    const size_t MAX_TABLE = 256;
};

#endif //HUFFMAN_CODE_HUFFMANCODE_HPP

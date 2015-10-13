#ifndef HUFFMAN_CODE_BITSOPERATION_HPP
#define HUFFMAN_CODE_BITSOPERATION_HPP

#include <string>

uint64_t    set_bit          (uint64_t, uint8_t);
uint8_t     get_bit          (uint64_t, uint8_t);
uint64_t    clear_bit        (uint64_t, uint8_t);
uint64_t    clear_all_bits   (uint64_t, uint8_t);

std::string convert_to_string(uint64_t, uint8_t);
uint64_t    convert_to_ulong (const std::string&);

#endif //HUFFMAN_CODE_BITSOPERATION_HPP

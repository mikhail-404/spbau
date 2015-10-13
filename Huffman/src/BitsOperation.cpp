#include "BitsOperation.hpp"

std::string convert_to_string(uint64_t number, uint8_t length)
{
    std::string binary_result(length, '0');
    int k = (int)length;
    while (number)
    {
        binary_result[--k] = char(number % 2 + 48);
        number >>= 1;
    }
    return binary_result;
}

uint64_t set_bit(uint64_t number, uint8_t i)
{
    return number | ((uint64_t)1 << i);
}

uint8_t get_bit(uint64_t number, uint8_t i)
{
    return static_cast <uint8_t>((number & (static_cast <uint64_t>(1) << i)) != 0);
}

uint64_t clear_bit(uint64_t number, uint8_t i)
{
    uint64_t mask = ~(static_cast <uint64_t>(1) << i);
    return number & mask;
}

uint64_t clear_all_bits(uint64_t number, uint8_t i)
{
    uint64_t mask = ~(((uint64_t)1 << (i + 1)) - 1);
    return number & mask;
}

uint64_t convert_to_ulong(const std::string &code)
{
    uint64_t result_number = 0;

    for(size_t i = 0; i < code.length(); ++i)
    {
        if (code[i] == '1')
            result_number = set_bit(result_number, code.length() - i - 1);
        else
            result_number = clear_bit(result_number, code.length() - i - 1);
    }

    return result_number;
}

#include "../include/bits_operations.hpp"

int set_bit(int number, unsigned char i)
{
    return number | (1 << i);
}

unsigned char get_bit(int number, unsigned char i)
{
    return (number & (1 << i)) != 0;
}

int clear_bit(int number, unsigned char i)
{
    int mask = ~(1 << i);
    return number & mask;
}

int clear_all_bits(int number, unsigned char i)
{
    int mask = ~((1 << (i + 1)) - 1);
    return number & mask;
}

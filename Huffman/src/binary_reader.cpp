#include "../include/binary_reader.hpp"

//
std::string int_to_binary_format(int number)
{
    std::string binary_code("");
    while (number)
    {
        binary_code = (number % 2 ? "1" : "0") + binary_code;
        number >>= 1;
    }
    return binary_code;
}

void cut_code(std::string &code, unsigned char last_pos)
{
    code.erase(0, code.length() - last_pos);
}

//
void decoder(std::ifstream &in, std::ofstream &out)
{
    //
    char dictionary_size;
    in.read((char*)&dictionary_size, sizeof(dictionary_size));

    //
    std::map <std::string, char> decode_dictionary;

    //
    std::string temp_code;
    for(int i = 0; i < (int)dictionary_size; ++i)
    {
        char current_char, size_code;
        in.read((char*)&current_char, sizeof(current_char));
        in.read((char*)&size_code, sizeof(size_code));
        int code;
        in.read((char*)&code, sizeof(code));

        temp_code = int_to_binary_format(code);
        cut_code(temp_code, (int)size_code);
        decode_dictionary[int_to_binary_format(code)] = current_char;
        //std::cout << current_char << ", " << (int)size_code << ", " << code << std::endl;
    }
}

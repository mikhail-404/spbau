#include "../include/binary_reader.hpp"

//
std::string int_to_binary_format(int number)
{
    if (!number)
        return "0";

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
    if (code.length() > last_pos)
        code.erase(0, code.length() - last_pos);
    else if (code.length() < last_pos)
    {
        for(size_t i = 0; i <= last_pos - code.length(); ++i)
            code = "0" + code;
    }
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
    int code;
    std::string temp_code;
    for(int i = 0; i < (int)dictionary_size; ++i)
    {
        char current_char, size_code;
        in.read((char*)&current_char, sizeof(current_char));
        in.read((char*)&size_code, sizeof(size_code));
        in.read((char*)&code, sizeof(code));

        temp_code = int_to_binary_format(code);
        cut_code(temp_code, (int)size_code);
        decode_dictionary[temp_code] = current_char;
        //std::cout << current_char << ": " << temp_code << std::endl;
    }

    temp_code = "";
    while (!in.eof())
    {
        in.read((char*)&code, sizeof(code));
        if (!in.eof())
        {
            std::cout << "Code: " << code << std::endl;
            temp_code = temp_code + int_to_binary_format(code);
        }
    }

    //std::cout << "Text: " << temp_code << std::endl;

    for(std::map <std::string, char>::iterator it = decode_dictionary.begin(); it != decode_dictionary.end(); ++it)
    {
        //std::cout << it->first << " -> " << it->second << std::endl;
    }
    std::cout << "=======================" << std::endl;

    std::string current(""), res("");
    for(size_t i = 0; i < temp_code.length(); ++i)
    {
        current += temp_code[i];
        if (decode_dictionary.find(current) != decode_dictionary.end())
        {
            //std::cout << current << " " << decode_dictionary[current] << std::endl;
            res += decode_dictionary[current];
            current.clear();
        }
    }
    std::cout << "Res: " << res << std::endl;
}

#include "../include/binary_writer.hpp"
#include "../include/huffman_tree.hpp"
#include "../include/features.hpp"
#include "../include/bits_operations.hpp"

#include <map>
#include <string>
#include <iostream>

int convert(const std::string &code_string)
{
    int binary_int_code = 0;
    for(int i = code_string.length() - 1; i >= 0; --i)
    {
        int current_pos = code_string.length() - i - 1;
        if (code_string[i] == '0')
            binary_int_code = clear_bit(binary_int_code, current_pos);
        else
            binary_int_code = set_bit(binary_int_code, current_pos);
    }
    return binary_int_code;
}

void binary_write_table_frequency(std::ofstream &out, const std::map <char, std::string> &dictionary)
{
    char dictionary_size = static_cast <char>(dictionary.size());
    out.write((char*)&dictionary_size, sizeof(dictionary_size));
    for(std::map <char, std::string>::const_iterator it = dictionary.begin(); it != dictionary.end(); ++it)
    {
        out.write((char*)&(it->first), sizeof(it->first));
        char code_size = static_cast <char>(it->second.length());
        out.write((char*)&code_size, sizeof(code_size));
        int convert_code_string = convert(it->second);
        out.write((char*)&convert_code_string, sizeof(convert_code_string));
    }
    std::cout << "Done" << std::endl;
}

void encoder(std::ifstream &in, std::ofstream &out)
{
    std::map <char, int> dictionary;
    char current_char;
    while (in >> current_char)
    {
        ++dictionary[current_char];
    }

    // передаем таблицу частотности символов для построения дерева кодов
    HuffmanTree huffman_tree(dictionary);
    // возвращаем результирующую таблицу с отображениями символ -> код
    std::map <char, std::string> code_table = huffman_tree.codes();
    // записываем таблицу в бинарный файл с признаком конца записи
    binary_write_table_frequency(out, code_table);
}

#include <map>
#include <string>
#include <iostream>

#include "../include/binary_writer.hpp"
#include "../include/huffman_tree.hpp"
#include "../include/bits_operations.hpp"
#include "../include/features.hpp"

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
    std::cout << "====== write ===========" << std::endl;
    for(std::map <char, std::string>::const_iterator it = dictionary.begin(); it != dictionary.end(); ++it)
    {
        out.write((char*)&(it->first), sizeof(it->first));
        char code_size = static_cast <char>(it->second.length());
        out.write((char*)&code_size, sizeof(code_size));
        int convert_code_string = convert(it->second);
        out.write((char*)&convert_code_string, sizeof(convert_code_string));
        std::cout << it->first << " -> " << it->second << std::endl;
    }
    std::cout << "=================" << std::endl;
}

void binary_write_text(std::ifstream &in, std::ofstream &out, std::map <char, std::string> dictionary)
{
    std::string temp("");
    char current_char;
    int current_number = 0;

    in.seekg(0, std::ios::beg);
    unsigned long t = 0;
    while (in.read(&current_char, 1))
    {
        temp += dictionary[current_char];
        if (temp.length() / BITS_SIZE)
        {
            std::string tmp(temp, 0, BITS_SIZE);
            current_number = convert(tmp);
            t += current_number;
            std::cout << "Current number: " << current_number << std::endl;
            out.write((char*)&current_number, sizeof(current_number));
            temp.erase(0, BITS_SIZE);
        }
    }

    if (temp.length() > 0)
    {
        current_number = convert(temp);
        t += current_number;
        std::cout << "Current number: " << current_number << std::endl;
        out.write((char*)&current_number, sizeof(current_number));
    }
    std::cout << "Sum = " << t << std::endl;
}

void encoder(std::ifstream &in, std::ofstream &out)
{
    std::map <char, int> dictionary;
    char current_char;
    while (in.read(&current_char, 1))
    {
        ++dictionary[current_char];
    }
    in.clear();

    // передаем таблицу частотности символов для построения дерева кодов
    HuffmanTree huffman_tree(dictionary);
    // возвращаем результирующую таблицу с отображениями символ -> код
    std::map <char, std::string> code_table = huffman_tree.codes();
    // записываем таблицу в бинарный файл с признаком конца записи
    binary_write_table_frequency(out, code_table);
    binary_write_text(in, out, code_table);
}

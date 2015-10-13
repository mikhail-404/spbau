#include <iostream>
#include <boost/program_options.hpp>

#include "HuffmanCode.hpp"

int main(int argc, char *argv[])
{
    try
    {
        namespace po = boost::program_options;

        po::options_description descriptions("Опции");
        descriptions.add_options()
                ("help,h", "Вывод сообщения с подсказками")
                (",c", "Кодирование")
                (",u", "Декодирование")
                ("file,f", po::value <std::string>()->required(), "Название входного файла")
                ("output,o", po::value <std::string>()->required(), "Название результирующего файла");

        po::variables_map variable;
        po::store(po::parse_command_line(argc, argv, descriptions), variable);

        if (variable.count("help"))
        {
            std::cout << "Подсказки по командам:" << std::endl << descriptions << std::endl;
            return 0;
        }

        std::string input_filename;
        std::string output_filename;

        if ((variable.count("file") && variable.count("output")))
        {
            input_filename  = variable["file"].as<std::string>();
            output_filename = variable["output"].as<std::string>();
        }

        HuffmanCode huffman(input_filename, output_filename);

        if (variable.count("-c"))
        {
            huffman.encode();
        }
        else if (variable.count("-u"))
        {
            huffman.decode();
        }
    }
    catch (FileIsNotFoundException &e)
    {
        std::cout << e.what() << std::endl;
    }
    return 0;
}
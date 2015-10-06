#include <iostream>
#include <fstream>
#include <string>

#include "../include/binary_writer.hpp"
#include "../include/binary_reader.hpp"
#include "../include/command_parser.hpp"

int main(int argc, char *argv[])
{
    /*
    //
    GetOptions options(argc, argv);
    //
    std::string input_file, output_file;
    input_file  = options.input_file();
    output_file = options.output_file();

    std::cout << input_file << " " << output_file << std::endl;

    std::ifstream in(input_file, std::ios::in);
    if (in.is_open())
    {
        std::ofstream out(output_file, std::ios::binary | std::ios::out);
        //
        if (options.is_compress())
        {
            std::cout << "Encode" << std::endl;
            encoder(in, out);
        }
        else if (options.is_uncompress())
        {
            std::cout << "Decode" << std::endl;
            decoder(in, out);
        }
        else
        {
            std::cout << "Commands are not found!" << std::endl;
        }
    }
    else
    {
        std::cout << "File [" << input_file << "] is not found" << std::endl;
    }
*/
    std::ifstream in  (argv[1], std::ios::binary | std::ios::in );
    std::ofstream out (argv[2], std::ios::binary | std::ios::out);

    encoder(in, out);

    in.close();
    out.close();
    in.open(argv[2], std::ios::binary | std::ios::in);
    out.open("../temp", std::ios::binary | std::ios::out);
    decoder(in, out);
    return 0;
}

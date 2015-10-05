#include <iostream>
#include <fstream>
#include <string>

#include "../include/binary_writer.hpp"
#include "../include/binary_reader.hpp"
#include <map>

int main(int argc, char *argv[])
{
    std::ifstream in(argv[1], std::ios::in);

    if (!in.is_open())
    {
        std::cout << "File is not found" << std::endl;
        return -1;
    }

    std::ofstream out(argv[2], std::ios::binary | std::ios::out);

    encoder(in, out);

    in.close();
    out.close();

    std::ifstream in2(argv[2], std::ios::binary | std::ios::in);
    std::ofstream out2("../input2", std::ios::out | std::ios::binary);

    decoder(in2, out2);

    return 0;
}

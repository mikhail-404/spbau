#include <iostream>
#include <fstream>
#include <string>

#include "../include/binary_writer.hpp"
#include <map>

int main(int argc, char *argv[])
{
    std::ifstream in("../input", std::ios::in);

    if (!in.is_open())
    {
        std::cout << "File is not found" << std::endl;
        return -1;
    }

    std::ofstream out("../output", std::ios::binary | std::ios::out);

    encoder(in, out);
    in.close();
    out.close();

    return 0;
}

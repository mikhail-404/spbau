#include <iostream>
#include "lint.hpp"

int main()
{
    try
    {
        lint number;
    }
    catch (std::exception &e)
    {
        std::cout << e.what() << std::endl;
    }
    return 0;
}


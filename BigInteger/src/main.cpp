#include <iostream>
#include "lint.hpp"
#include <vector>
#include <string>

int main()
{
    try
    {
        const std::string n("10000000004");
        const std::string m("1");
        lint a(n);
        lint b(m);
        a -= 100000011;
        std::cout << a << std::endl;
    }
    catch (std::exception &e)
    {
        std::cout << e.what() << std::endl;
    }
    return 0;
}


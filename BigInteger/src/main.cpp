#include <iostream>
#include "lint.hpp"
#include <vector>
#include <string>

int main()
{
    try
    {
        const std::string n("12");
        const std::string m("3");
        lint a(n);
        lint b(m);
        lint c = a / b;
        std::cout << c << std::endl;
        //std::cout << std::numeric_limits <double>::max() << std::endl;
    }
    catch (std::exception &e)
    {
        std::cout << e.what() << std::endl;
    }
    return 0;
}


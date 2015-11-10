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
        lint b(-1111111111);
        std::string result = b.to_string();
        if (b)
        {
            std::cout << "true" << std::endl;
        }
        else
            std::cout << "false" << std::endl;
        std::cout << result << std::endl;
    }
    catch (std::exception &e)
    {
        std::cout << e.what() << std::endl;
    }
    return 0;
}


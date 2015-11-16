#include <iostream>
#include "lint.hpp"
#include <vector>

int main()
{
    try
    {
//        BigInteger a("9999999999999999999999999999999999999999999999999999999123123123123123123123123199"),
//                b("947823642346827346237846238746823847264234878"), d(12);
//        BigInteger c = a * b;
//        std::cout << c << std::endl;
        BigInteger a(-1);
        std::cout << a-- << std::endl;
        std::cout << a << std::endl;

    }
    catch (std::exception &e)
    {
        std::cout << e.what() << std::endl;
    }
    return 0;
}

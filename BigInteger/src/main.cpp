#include <iostream>
#include "lint.hpp"
#include <vector>
#include "test.hpp"

int main()
{
    try
    {
////        BigInteger a("9999999999999999999999999999999999999999999999999999999123123123123123123123123199"),
////                b("947823642346827346237846238746823847264234878"), d(12);
////        BigInteger c = a * b;
////        std::cout << c << std::endl;
//        BigInteger a("12000000000000000000000000000000000000000000000000000000000000000000000000000000"), b("12312312312312312312312312312312312313");
//        BigInteger c = a / b;
//        std::cout << c << std::endl;
//        BigInteger a = 2, b = 3;
//        std::cout << (3.14 < a) << std::endl;
//        std::cout << (a != b) << std::endl;
//        std::cout << (5 > a) << std::endl;
//        std::cout << (a == b) << std::endl;
//        std::cout << (5 <= b) << std::endl;
//        std::cout << (a >= 6) << std::endl;


        test_construction();
        test_conversions();
        failed_conversions_test();
        test_comparison();
        test_check();
        test_inc_n_dec();
        test_op_n_eq();
        test_bin_op();
        test_free_func();
        test_io();

    }
    catch (std::exception &e)
    {
        std::cout << e.what() << std::endl;
    }
    return 0;
}

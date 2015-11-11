#include <iostream>
#include "double_number.hpp"
#include <cmath>

int main()
{
    imprecise::DoubleNumber value(0.43);
    std::cout << value << std::endl;
    std::cout << "My sin:  " << imprecise::sin(value)  << " Std sin: " << std::sin(value.value()) << std::endl;
    std::cout << "My cos:  " << imprecise::cos(value)  << " Std sin: " << std::cos(value.value()) << std::endl;
    std::cout << "My sqrt: " << imprecise::sqrt(value) << " Std sin: " << std::sqrt(value.value()) << std::endl;
    return 0;
}


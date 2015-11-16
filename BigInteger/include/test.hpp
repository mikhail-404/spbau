#include <iostream>
#include <sstream>
#include <assert.h>
#include <lint.hpp>

//#define RUN_FAILED_COMP_TEST

using namespace apa;

static void test_construction()
{
    BigInteger x;
    const BigInteger y(x);
    x = y;
    x = x;
    (void)test_construction;
}

static void test_conversions()
{
    int ordinary = 42;
    BigInteger long_int(ordinary);
    long_int = ordinary;
    ordinary = static_cast<int>(long_int); // ok
    std::string s("-15");
    BigInteger z(s);
    z.to_string() == s;
    (void)test_conversions;
}

static void failed_conversions_test()
{
#ifdef RUN_FAILED_COMP_TEST
    int ordinary = 42;
    std::string str = "-42";
    BigInteger x = 5;
    ordinary = x; // must be compilation error!
    X = str; // must be compilation error!
    Str = x; // must be compilation error!
#endif
    (void)failed_conversions_test;
}

static inline void test_comparison()
{
    BigInteger long_int1 = 2;
    BigInteger long_int2 = 3.; // constructing from double value
    BigInteger neglint1 = -2;
    BigInteger neglint2 = -13.;
    BigInteger zero = 0;
    BigInteger dzero = 0.0;

    bool check = true;
    // positive comparisons
    check &= long_int1 < 3.14;
    check &= !(long_int1 > 3.14);
    check &= long_int1 > 1;
    check &= !(long_int1 < 1);
    check &= long_int1 == 2;
    check &= 2 == long_int1;
    check &= !(long_int1 != 2);
    check &= !(2 != long_int1);
    check &= 5 > long_int1;
    check &= !(5 < long_int1);
    check &= !(long_int1 == long_int2);
    check &= long_int1 != long_int2;
    check &= 5 >= long_int2;

    // negative comparisons
    check &= neglint1 > neglint2;
    check &= neglint1 >= neglint2;
    check &= !(neglint1 < neglint2);
    check &= !(neglint1 <= neglint2);
    check &= !(neglint1 == neglint2);
    check &= neglint2 < neglint1;
    check &= neglint2 <= neglint1;
    check &= neglint1 != neglint2;

    // comparisons with different signs;
    check &= long_int1 > neglint1;
    check &= long_int1 > neglint2;
    check &= long_int2 > neglint1;
    check &= long_int2 > neglint2;
    check &= neglint1 < long_int1;
    check &= neglint2 < long_int2;
    check &= !(neglint1 == long_int1);
    check &= neglint1 != long_int1;

    // comparisons with zero
    check &= zero == dzero;
    check &= !(zero != dzero);
    check &= zero > neglint1;
    check &= zero < long_int2;
    check &= dzero > neglint2;
    check &= dzero < long_int1;
    check &= dzero != neglint1;
    check &= zero != long_int2;
    assert(check);
    (void)test_comparison;
}

static void test_check()
{
    BigInteger value = 0;
    if (value)
        std::cout << "non zero value" << std::endl;
    (void)test_check;
}

static void test_inc_n_dec()
{
    BigInteger x = 42;
    BigInteger y = ++x;
    assert(y == 43 && x == 43);
    y = x--;
    assert(y == 43 && x == 42);
    (void)test_inc_n_dec;
}

static void test_op_n_eq()
{
    BigInteger a = 123456;
    const BigInteger b = 789012;
    BigInteger c = a * b;
    a *= b;
    a += b;
    c /= a;
    c -= c;
    a /= c; // division by zero
    (void)test_op_n_eq;
}

static void test_bin_op()
{
    BigInteger a = 123456789;
    const BigInteger b = 987654321;
    BigInteger c = a * b;
    BigInteger d = 3.14 + c;
    c = a * b;
    c = a + b;
    c = c / a;
    c = c + (-c);
    c = a / c; // division by zero
    c = +c;
    assert(d); //avoid warning
    (void)test_bin_op;
}

static void test_free_func()
{
    apa::BigInteger a = -42;
    bool check = (-a == abs(a));
    apa::BigInteger c = pow(a, 0);
    check = check && (c == 1);
    assert(check);
    (void)test_free_func;
}

static void test_io()
{
    std::stringstream s;
    const BigInteger a = -123454321;
    s << a;
    BigInteger b;
    s >> b;
    bool check = a == b;
    assert(check);

    std::stringstream s2("+00015");
    BigInteger c;
    s2 >> c;
    assert(c == 15);

    (void)test_io;
}

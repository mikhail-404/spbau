#ifndef LINT_HPP
#define LINT_HPP

#include <iostream>
#include <string>
#include "long_array.hpp"

class BigInteger
{
public:
    //
    BigInteger();
    //
    BigInteger(int int_number);
    BigInteger(double float_number);
    //
    BigInteger(const std::string string_number);
    //
    BigInteger(const BigInteger &number);
    //
    BigInteger& operator= (const BigInteger &number);
    //
    explicit operator int();
    explicit operator double();
    explicit operator bool();
    //
    std::string to_string() const;
    //
    BigInteger& operator+= (const BigInteger &number);
    BigInteger& operator-= (const BigInteger &number);
    BigInteger& operator*= (const BigInteger &number);
    BigInteger& operator/= (const BigInteger &number);
    //
    BigInteger operator+ ();
    BigInteger operator- ();
    //
    friend bool operator<  (const BigInteger &a, const BigInteger &b);
    friend bool operator== (const BigInteger &a, const BigInteger &b);
    //
    BigInteger& operator++ ();
    BigInteger& operator-- ();
    BigInteger  operator++ (int);
    BigInteger  operator-- (int);
    //

private:
    //
    BigInteger add (const BigInteger &a, const BigInteger &b);
    BigInteger sub (const BigInteger &a, const BigInteger &b);
    BigInteger mult(const BigInteger &a, const BigInteger &b);
    BigInteger div (const BigInteger &a, const BigInteger &b);
    //
    void       swap(BigInteger &number);

private:
    char                  m_sign;
    long_array            m_array;
    static constexpr int  m_base        = 1e9;
    static constexpr int  m_base_degree = 9;
};

//
std::istream& operator>> (std::istream &ist, BigInteger &number);
std::ostream& operator<< (std::ostream &ost, const BigInteger &number);
//
BigInteger operator+ (const BigInteger &a, const BigInteger &b);
BigInteger operator- (const BigInteger &a, const BigInteger &b);
BigInteger operator* (const BigInteger &a, const BigInteger &b);
BigInteger operator/ (const BigInteger &a, const BigInteger &b);
//
bool operator<= (const BigInteger &a, const BigInteger &b);
bool operator>  (const BigInteger &a, const BigInteger &b);
bool operator>= (const BigInteger &a, const BigInteger &b);
bool operator!= (const BigInteger &a, const BigInteger &b);
//
BigInteger abs(BigInteger number);
BigInteger pow(const BigInteger &number, int degree);
//
uint32_t    str_to_int(const std::string &number);
std::string int_to_str(uint32_t number);
//
#endif // LINT_HPP

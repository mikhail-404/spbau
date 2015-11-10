#ifndef LINT_HPP
#define LINT_HPP

#include <iostream>
#include <string>
#include <limits>

#include "long_array.hpp"

class lint
{
public:
    //
    lint();
    lint(const lint &big_number);
    lint& operator= (const lint &big_number);
    ~lint();
    //
    lint(int int_number);
    lint(double double_number);
    lint(const std::string &string_number);
    //
    lint& operator= (int int_number);
    lint& operator= (double double_number);
    lint& operator= (std::string string_number);
    //
    operator uint64_t();
    operator int();
    operator bool();
    //
    std::string to_string() const;
    //
    lint& operator++ ();
    lint& operator-- ();
    lint operator++ (int);
    lint operator-- (int);
    //
    lint operator+ ();
    lint operator- ();
    //
    lint operator+ (const lint &a);
    lint operator- (const lint &a);
    lint operator* (const lint &a);
    lint operator/ (const lint &a);
    //
    lint operator- (int a);
    lint operator+ (const int a);
    lint operator* (const int a);
    lint operator/ (const int a);
    //
    lint& operator+= (const lint &number);
    lint& operator-= (const lint &number);
    lint& operator*= (const lint &number);
    lint& operator/= (const lint &number);
    //
    lint& operator+= (const int a);
    lint& operator-= (const int a);
    lint& operator*= (const int a);
    lint& operator/= (const int a);
    //
    bool operator<  (const lint &number) const; // +
    bool operator>  (const lint &number) const; // +
    bool operator<= (const lint &number) const; // +
    bool operator>= (const lint &number) const; // +
    bool operator== (const lint &number) const; // +
    bool operator!= (const lint &number) const; // +
    //
    bool operator<  (int number) const;
    bool operator>  (int number) const;
    bool operator<= (int number) const;
    bool operator>= (int number) const;
    bool operator== (int number) const;
    bool operator!= (int number) const;
    //
    friend std::istream& operator>> (std::istream &ist, lint &number);
    friend std::ostream& operator<< (std::ostream &ost, const lint &number);  // +
    friend lint abs(const lint &number); // +
    //

private:
    void copy_lint(const lint &number);
    void set_abs();
    void swap(lint &number);

private:
    long_array       m_array;
    char             m_sign;     // true - positive, false - negative
    const uint32_t   m_base = 1000000000; // 1e9
    const uint       m_base_degree = 9;
};

uint32_t    str_to_int(const std::string &number);
std::string int_to_str(uint32_t number);

#endif // LINT_HPP

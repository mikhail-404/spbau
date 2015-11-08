#ifndef LINT_HPP
#define LINT_HPP

#include <iostream>
#include <string>

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
    lint(double doulbe_number);
    lint(const std::string &string_number);
    //
    operator uint64_t();
    operator bool();
    //
    std::string to_string() const;
    //
    friend std::istream& operator>> (std::istream &ist, lint &number);
    friend std::ostream& operator<< (std::ostream &ost, const lint &number);
    //
    lint& operator++ ();
    lint& operator-- ();
    lint& operator++ (int);
    lint& operator-- (int);
    //
    lint operator+ (const lint &a);
    lint operator- (const lint &a);
    lint operator* (const lint &a);
    lint operator/ (const lint &a);
    //
    lint& operator += (const lint &number);
    lint& operator -= (const lint &number);
    lint& operator *= (const lint &number);
    lint& operator /= (const lint &number);
    //
    bool operator<  (const lint &number) const;
    bool operator>  (const lint &number) const;
    bool operator<= (const lint &number) const;
    bool operator>= (const lint &number) const;
    bool operator== (const lint &number) const;
    bool operator!= (const lint &number) const;
    //

private:
    long_array m_array;
    bool       m_sign; // true - positive, false - negative
    size_t     m_base;
};

#endif // LINT_HPP

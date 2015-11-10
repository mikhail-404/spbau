#ifndef DOUBLE_NUMBER_HPP
#define DOUBLE_NUMBER_HPP

#include <iostream>

class DoubleNumber
{
public:
    //
    DoubleNumber();
    DoubleNumber(double value);
    DoubleNumber(double value, double delta_in);
    //
    DoubleNumber(const DoubleNumber &number);
    //
    DoubleNumber& operator= (const DoubleNumber &number);
    //
    double value() const;
    double delta() const;
    //
    DoubleNumber& operator- ();
    //
    DoubleNumber& operator+= (const DoubleNumber &number);
    DoubleNumber& operator-= (const DoubleNumber &number);
    DoubleNumber& operator*= (const DoubleNumber &number);
    DoubleNumber& operator/= (const DoubleNumber &number);
    //
    friend DoubleNumber operator+ (const DoubleNumber &a, const DoubleNumber &b);
    friend DoubleNumber operator- (const DoubleNumber &a, const DoubleNumber &b);
    friend DoubleNumber operator* (const DoubleNumber &a, const DoubleNumber &b);
    friend DoubleNumber operator/ (const DoubleNumber &a, const DoubleNumber &b);
    //
    friend std::ostream& operator<< (std::ostream &ost, const DoubleNumber &number);
    friend std::istream& operator>> (std::istream &ist, DoubleNumber &number);
    //
    bool operator<  (const DoubleNumber &number);
    bool operator>  (const DoubleNumber &number);
    bool operator<= (const DoubleNumber &number);
    bool operator>= (const DoubleNumber &number);
    bool operator== (const DoubleNumber &number);
    bool operator!= (const DoubleNumber &number);

private:
    void swap(DoubleNumber &number);

private:
    double m_value;
    double m_delta;
};

#endif // DOUBLE_NUMBER_HPP

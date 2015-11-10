#include "double_number.hpp"

DoubleNumber::DoubleNumber()
{

}

DoubleNumber::DoubleNumber(double value)
    : m_value(value),
      m_delta(1e-15 * value)
{

}

DoubleNumber::DoubleNumber(double value, double delta_in)
    : m_value(value),
      m_delta(std::max(delta_in, 1e-15 * value))
{

}

DoubleNumber::DoubleNumber(const DoubleNumber &number)
    : m_value(number.m_value),
      m_delta(number.m_delta)
{

}

DoubleNumber& DoubleNumber::operator= (const DoubleNumber &number)
{
    DoubleNumber(number).swap(*this);
    return *this;
}

double DoubleNumber::value() const
{
    return m_value;
}

double DoubleNumber::delta() const
{
    return m_delta;
}

DoubleNumber &DoubleNumber::operator-()
{
    m_value *= -1;
    return *this;
}

bool DoubleNumber::operator< (const DoubleNumber &number)
{
    return m_value + m_delta < number.m_value - number.m_delta;
}

bool DoubleNumber::operator> (const DoubleNumber &number)
{
    return m_value + m_delta > number.m_value - number.m_delta;
}

bool DoubleNumber::operator<= (const DoubleNumber &number)
{
    return (*this < number || *this == number);
}

bool DoubleNumber::operator>= (const DoubleNumber &number)
{
    return (*this > number || *this == number);
}

bool DoubleNumber::operator== (const DoubleNumber &number)
{
    return !(*this < number) && !(*this > number);
}

bool DoubleNumber::operator!= (const DoubleNumber &number)
{
    return !(*this == number);
}

std::istream& operator>>(std::istream &ist, DoubleNumber &number)
{
    ist >> number.m_delta >> number.m_delta;
    return ist;
}

std::ostream& operator<<(std::ostream &ost, const DoubleNumber &number)
{
    ost << number.m_value << " " << number.m_delta;
    return ost;
}

DoubleNumber& DoubleNumber::operator+= (const DoubleNumber &number)
{
    *this = *this + number;
    return *this;
}

DoubleNumber& DoubleNumber::operator-= (const DoubleNumber &number)
{
    *this = *this - number;
    return *this;
}

DoubleNumber& DoubleNumber::operator*= (const DoubleNumber &number)
{
    *this = *this * number;
    return *this;
}

DoubleNumber& DoubleNumber::operator/= (const DoubleNumber &number)
{
    *this = *this / number;
    return *this;
}

void DoubleNumber::swap(DoubleNumber &number)
{
    std::swap(m_value, number.m_value);
    std::swap(m_delta, number.m_delta);
}

DoubleNumber operator+ (const DoubleNumber &a, const DoubleNumber &b)
{
    DoubleNumber temp(a);
    temp.m_value += b.m_value;
    temp.m_delta += b.m_delta;
    return temp;
}

DoubleNumber operator- (const DoubleNumber &a, const DoubleNumber &b)
{
    DoubleNumber temp(a);
    temp.m_value -= b.m_value;
    temp.m_delta -= b.m_delta;
    return temp;
}

DoubleNumber operator* (const DoubleNumber &a, const DoubleNumber &b)
{
    DoubleNumber temp(a);
    temp.m_value *= b.m_value;
    temp.m_delta  = temp.m_delta * b.m_value + b.m_delta * temp.m_value;
    return temp;
}

DoubleNumber operator/ (const DoubleNumber &a, const DoubleNumber &b)
{
    DoubleNumber temp(a);
    temp.m_value /= b.m_value;
    temp.m_delta  = temp.m_delta / b.m_value + (temp.m_value * b.m_delta / b.m_value / b.m_value);
    return temp;
}

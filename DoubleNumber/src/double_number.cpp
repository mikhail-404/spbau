#include "double_number.hpp"
#include <cmath>

namespace imprecise
{

DoubleNumber::DoubleNumber()
    : m_value(0.0)
{

}

DoubleNumber::DoubleNumber(double value)
    : m_value(value),
      m_delta(NUM_EXP * value)
{

}

DoubleNumber::DoubleNumber(double value, double delta_in)
    : m_value(value),
      m_delta(std::max(delta_in, NUM_EXP * value))
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

DoubleNumber DoubleNumber::operator-()
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
    double al = m_value - m_delta;
    double ar = m_value + m_delta;
    double bl = number.m_value - number.m_delta;
    double br = number.m_value + number.m_delta;
    return (al <= bl && bl <= ar) || (al <= br && br <= ar);
}

bool DoubleNumber::operator!= (const DoubleNumber &number)
{
    return !(*this == number);
}

std::istream& operator>>(std::istream &ist, DoubleNumber &number)
{
    ist >> number.m_value >> number.m_delta;
    number.m_delta = number.m_value * number.NUM_EXP; // or number = DoubleNumber(value, delta)
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
    temp.m_delta += b.m_delta;
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

DoubleNumber sin(const DoubleNumber &a)
{
    double y = a.value(), sum = 0.0, x = a.value();
    size_t i = 0;
    while (std::fabs(y) >= a.delta())
    {
        sum += y;
        ++i;
        y = -y * x * x / 2 / i / (2 * i + 1);
    }
    return DoubleNumber(sum);
}

DoubleNumber cos(const DoubleNumber &a)
{
    double y = 1, sum = 0.0, x = a.value();
    size_t i = 0;
    while (std::fabs(y) >= a.delta())
    {
        sum += y;
        ++i;
        y = -y * x * x / 2 / i / (2 * i - 1);
    }
    return DoubleNumber(sum);
}

DoubleNumber sqrt(const DoubleNumber &a)
{
    double y = a.value(), y_prev = 0.0;
    while (std::fabs(y - y_prev) >= a.delta())
    {
        y_prev = y;
        y = (y + a.value() / y) * 0.5;
    }
    return DoubleNumber(y);
}


} // namespace imprecise

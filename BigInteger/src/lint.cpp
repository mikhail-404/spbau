#include "lint.hpp"

// +
BigInteger::BigInteger()
    : BigInteger("0")
{
}

// +
BigInteger::BigInteger(int int_number)
    : BigInteger(std::to_string(int_number))
{
}

// +
BigInteger::BigInteger(double float_number)
    : BigInteger(std::to_string(float_number))
{
}

// +
BigInteger::BigInteger(const std::string string_number)
{
    std::string number = string_number;
    size_t point_pos = number.find('.');
    // for floating-point
    if (point_pos != std::string::npos)
        number.erase(number.begin() + point_pos, number.end());

    m_sign = number[0] == '-' ? -1 : 1;
    if (number[0] == '-' || number[0] == '+')
        number.erase(0, 1);
    int size = static_cast <int>(number.size());
    int degree = static_cast <int>(m_base_degree);
    for(int i = size; i > 0; i -= degree)
    {
        if (i < degree)
            m_array.push_back(str_to_int(number.substr(0, i)));
        else
            m_array.push_back(str_to_int(number.substr(i - degree, degree)));
    }
}

// +
BigInteger::BigInteger(const BigInteger &number)
{
    m_array = number.m_array;
    m_sign  = number.m_sign;
}

// +
BigInteger& BigInteger::operator=(const BigInteger &number)
{
    BigInteger(number).swap(*this);
    return *this;
}

// +
std::string BigInteger::to_string() const
{
    std::string result;
    int size = static_cast <int>(m_array.size());
    if (size == 1 && m_array[0] == 0)
        return "0";

    result.reserve(size * m_base_degree + 1);
    if (m_sign < 0)
        result = '-';

    for(int i = size - 1; i >= 0; --i)
    {
        uint32_t k = m_base / 10;
        while (m_array[i] < k && i != size - 1)
        {
            result += "0";
            k /= 10;
        }
        result += int_to_str(m_array[i]);
    }
    return result;
}

// +
BigInteger& BigInteger::operator+= (const BigInteger &number)
{
    if (m_sign > 0 && number.m_sign > 0)
    {
        *this = add(*this, number);
        m_sign = 1;
    }
    else if (m_sign < 0 && number.m_sign < 0)
    {
        *this = add(*this, number);
        m_sign = -1;
    }
    else if (m_sign < 0 && number.m_sign > 0)
    {
        *this = sub(number, abs(*this));
        m_sign = 1;
    }
    else if (*this < number)
    {
        if (abs(*this) > number)
        {
            BigInteger temp(abs(*this));
            *this = sub(temp, number);
            m_sign = -1;
        }
        else
        {
            BigInteger temp(number);
            temp -= abs(*this);
            *this = temp;
            m_sign = 1;
        }
    }
    else if (*this >= number)
    {
        if (*this > abs(number))
        {
            BigInteger temp(*this);
            *this = sub(temp, abs(number));
            m_sign = 1;
        }
        else
        {
            BigInteger temp(abs(number));
            temp -= *this;
            temp.m_sign = -1;
            *this = temp;
            m_sign = 1;
        }
    }
    return *this;
}

// +
BigInteger& BigInteger::operator-= (const BigInteger &number)
{
    if (m_sign < 0 && number.m_sign > 0)
    {
        *this = add(abs(*this), abs(number));
        m_sign = -1;
    }
    else if (m_sign > 0 && number.m_sign > 0)
    {
        if (*this < number)
        {
            *this = sub(number, *this);
            m_sign = -1;
        }
        else
        {
            *this = sub(*this, number);
            m_sign = 1;
        }
    }
    else if (m_sign < 0 && number.m_sign < 0)
    {
        if (abs(*this) < abs(number))
        {
            *this = sub(abs(number), abs(*this));
            m_sign = 1;
        }
        else
        {
            *this = sub(abs(*this), abs(number));
            m_sign = -1;
        }
    }
    else if (m_sign > 0 && number.m_sign < 0)
    {
        *this = add(*this, abs(number));
        m_sign = 1;
    }
    return *this;
}

// +
BigInteger& BigInteger::operator*= (const BigInteger &number)
{
    char sign = m_sign * number.m_sign;
    *this = mult(*this, number);
    m_sign = sign;
    return *this;
}

BigInteger& BigInteger::operator/= (const BigInteger &number)
{
    if (number == 0)
        ;

    char sign = m_sign * number.m_sign;
    *this = div(*this, number);
    m_sign = sign;
        return *this;
    return *this;
}

// +
BigInteger BigInteger::operator+ ()
{
    return *this;
}

// +
BigInteger BigInteger::operator- ()
{
    BigInteger temp(*this);
    temp.m_sign *= -1;
    return temp;
}

// +
BigInteger& BigInteger::operator++ ()
{
    *this += 1;
    return *this;
}

// +
BigInteger& BigInteger::operator-- ()
{
    *this -= 1;
    return *this;
}

// +
BigInteger BigInteger::operator++ (int)
{
    BigInteger temp(*this);
    *this += 1;
    return temp;
}

// +
BigInteger BigInteger::operator-- (int)
{
    BigInteger temp(*this);
    *this -= 1;
    return temp;
}

// +
BigInteger BigInteger::add(const BigInteger &a, const BigInteger &b)
{
    BigInteger temp(a);
    size_t carry = 0, i = 0;
    while (i < std::max(temp.m_array.size(), b.m_array.size()) || carry)
    {
        if (i == temp.m_array.size())
            temp.m_array.push_back(0);
        temp.m_array[i] += carry + (i < b.m_array.size() ? b.m_array[i] : 0);
        carry = temp.m_array[i] >= temp.m_base;
        if (carry)
            temp.m_array[i] -= temp.m_base;
        ++i;
    }
    return temp;
}

// +
BigInteger BigInteger::sub(const BigInteger &a, const BigInteger &b)
{
    BigInteger temp(a);
    size_t carry = 0;
    for(int i = 0; i < b.m_array.size() || carry; ++i)
    {
        temp.m_array[i] -= carry + (i < b.m_array.size() ? b.m_array[i] : 0);
        carry = temp.m_array[i] < 0;
        if (carry)
            temp.m_array[i] += temp.m_base;
    }
    while (temp.m_array.size() > 1 && temp.m_array.back() == 0)
        temp.m_array.pop_back();
    return temp;
}

// +
BigInteger BigInteger::mult(const BigInteger &a, const BigInteger &b)
{
    BigInteger temp;
    for(size_t i = 0; i < a.m_array.size() + b.m_array.size(); ++i)
        temp.m_array.push_back(0);
    for(size_t i = 0; i < a.m_array.size(); ++i)
        for(size_t j = 0, carry = 0; j < b.m_array.size() || carry; ++j)
        {
            uint64_t current =
                    temp.m_array[i + j] + a.m_array[i] * 1ll *
                    (j < static_cast <int>(b.m_array.size()) ? b.m_array[j] : 0) + carry;
            temp.m_array[i + j] = static_cast <uint32_t>(current % a.m_base);
            carry = static_cast <size_t>(current / a.m_base);

        }
    while (temp.m_array.size() > 1 && temp.m_array.back() == 0)
        temp.m_array.pop_back();
    return temp;
}

// fuck off
BigInteger BigInteger::div(const BigInteger &a, const BigInteger &b)
{
    if (b > a)  return 0;
    BigInteger res;
    res.m_array.resize(a.m_array.size());
    BigInteger curValue;
    int size = static_cast <int>(a.m_array.size());
    for(int i = size - 1; i >= 0; --i)
    {
        curValue *= a.m_base;
        curValue.m_array[0] = a.m_array[i];
        uint32_t x = 0, l = 0, r = a.m_base;
        while (l <= r)
        {

            uint32_t m = (l + r) / 2;
            BigInteger cur = b * (int)m;
            std::cout << l << " " << r << " -> " << cur << " " << curValue << std::endl;
            if (cur <= curValue)
            {
                x = m;
                l = m + 1;
            }
            else
                r = m - 1;
        }
        res.m_array[i] = x;
        curValue -= b * (int)x;
    }

    size = res.m_array.size() - 1;
    while (size >= 0 && !res.m_array.back())
        res.m_array.pop_back();
    return res;
}

// +
void BigInteger::swap(BigInteger &number)
{
    std::swap(m_array, number.m_array);
    std::swap(m_sign,  number.m_sign);
}

// +
BigInteger::operator bool ()
{
    return !(m_array.size() == 1 && m_array[0] == 0);
}

// ?
BigInteger::operator double ()
{
    return 0;
}

// ?
BigInteger::operator int ()
{
    return 0;
}

// ?
std::istream &operator>>(std::istream &ist, BigInteger &number)
{
    std::string string_number;
    ist >> string_number;
    number = BigInteger(string_number);
    return ist;
}

// +
std::ostream &operator<<(std::ostream &ost, const BigInteger &number)
{
    ost << number.to_string();
    return ost;
}

// + recursive definition =)
bool operator< (const BigInteger &a, const BigInteger &b)
{
    if (a.m_sign < b.m_sign)
        return true;
    if (a.m_sign > b.m_sign)
        return false;
    // a < 0 AND b < 0
    if (a.m_sign < 0)
        return abs(b) < abs(a);

    if (a.m_array.size() != b.m_array.size())
        return a.m_array.size() < b.m_array.size();

    int size = static_cast <int>(a.m_array.size());
    for(int i = size - 1; i >= 0; --i)
        if (a.m_array[i] < b.m_array[i])
            return true;
    return false;
}

// +
bool operator== (const BigInteger &a, const BigInteger &b)
{
    if (a.m_sign * b.m_sign < 0)
        return false;
    if (a.m_array.size() != b.m_array.size())
        return false;
    int size = static_cast <int>(a.m_array.size());
    for(int i = size - 1; i >= 0; --i)
        if (a.m_array[i] != b.m_array[i])
            return false;
    return true;
}

// +
bool operator<= (const BigInteger &a, const BigInteger &b)
{
    return !(b < a);
}

// +
bool operator> (const BigInteger &a, const BigInteger &b)
{
    return b < a;
}

// +
bool operator>= (const BigInteger &a, const BigInteger &b)
{
    return !(a < b);
}

// +
bool operator!= (const BigInteger &a, const BigInteger &b)
{
    return !(a == b);
}

// +
BigInteger abs(BigInteger number)
{
    return (number < 0 ? -number : number);
}

// +
BigInteger pow(const BigInteger &number, int degree)
{
    if (!degree)
        return 1;
    BigInteger temp(number), result(1);
    while (degree)
    {
        if (degree & 1)
            result *= temp;
        temp *= temp;
        degree >>= 1;
        std::cout << degree << std::endl;
    }
    return result;
}

// +
uint32_t str_to_int(const std::string &number)
{
    uint32_t result = 0;
    for(size_t i = 0; i < number.size(); ++i)
        result = result * 10 + (number[i] - '0');
    return result;
}

// +
std::string int_to_str(uint32_t number)
{
    std::string result;
    result.reserve(10);
    while (number)
    {
        result = static_cast <char>(number % 10 + '0') + result;
        number /= 10;
    }
    return result;
}

// +
BigInteger operator+ (const BigInteger &a, const BigInteger &b)
{
    BigInteger temp(a);
    temp += b;
    return temp;
}

// +
BigInteger operator- (const BigInteger &a, const BigInteger &b)
{
    BigInteger temp(a);
    temp -= b;
    return temp;
}

// +
BigInteger operator* (const BigInteger &a, const BigInteger &b)
{
    BigInteger temp(a);
    temp *= b;
    return temp;
}

BigInteger operator/ (const BigInteger &a, const BigInteger &b)
{
    BigInteger temp(a);
    temp /= b;
    return temp;
}

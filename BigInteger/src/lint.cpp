#include "lint.hpp"
#include <cmath>

//
lint::lint()
{
    set_abs();  // +
}

// +
void lint::copy_lint(const lint &number)
{
    m_sign  = number.m_sign;
    m_array = number.m_array;
}

void lint::set_abs()
{
    m_sign = 1;
}

// +
lint::lint(const lint &big_number)
{
   copy_lint(big_number);
}

void lint::swap(lint &number)
{
    std::swap(m_array, number.m_array);
    std::swap(m_sign, number.m_sign);
}

void lint::level_up()
{
    size_t size = m_array.size();
    m_array.reserve(size + 1);
    for(size_t i = size - 1; i >= 1; --i)
        m_array[i] = m_array[i - 1];
}

lint lint::add(const lint &a, const lint &b)
{
    lint temp(a);
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
lint& lint::operator= (const lint &big_number)
{
    //copy_lint(big_number);
    lint(big_number).swap(*this);
    return *this;
}

// +
lint::~lint()
{
    // ~m_array
}

// +
lint::lint(int int_number)
{
    m_sign = int_number > 0 ? 1 : (int_number < 0 ? -1 : 0);
    m_array.push_back(std::abs(int_number));
}

lint::lint(double double_number)
{
    m_sign = double_number > 0.0 ? 1 : (double_number < 0.0 ? -1 : 0);
}

// +
lint::lint(const std::string &string_number)
{
    std::string number = string_number;
    m_sign = number[0] == '-' ? -1 : 1;
    if (number[0] == '-' || number[0] == '+')
        number.erase(0, 1);
    int string_size = static_cast <int>(number.size());
    for(int i = string_size; i > 0; i -= m_base_degree)
        if (i < static_cast <int>(m_base_degree))
            m_array.push_back(str_to_int(number.substr(0, i)));
        else
            m_array.push_back(str_to_int(number.substr(i - m_base_degree, m_base_degree)));
}

// +
lint &lint::operator= (int int_number)
{
    lint temp(std::abs(int_number));
    swap(temp);
    if (int_number < 0)
        m_sign = -1;
    return *this;
}

lint &lint::operator= (double int_number)
{
    return *this;
}

// +
lint& lint::operator= (std::string string_number)
{
    lint temp(string_number);
    swap(temp);
    return *this;
}

lint::operator int()
{
    return 0;
}

lint::operator uint64_t()
{
    //uint64_t max_uint64 = std::numeric_limits <uint64_t>::max();

    return 0;
}

// +
lint::operator bool()
{
    return !(m_array.size() == 1 && m_array[0] == 0);
}

// +
std::string lint::to_string() const
{
    std::string result;
    int size = static_cast <int>(m_array.size());
    result.reserve(size * m_base_degree + 1);

    if (m_sign < 0)
        result += '-';

    for(int i = size - 1; i >= 0; --i)
    {
        uint32_t k = m_base / 10;
        while (m_array[i] < k && i != size - 1)
        {
            result += '0';
            k /= 10;
        }
        result += int_to_str(m_array[i]);
    }
    return result;
}

//
std::istream& operator>> (std::istream &ist, lint &number)
{
    return ist;
}

// +
std::ostream& operator<< (std::ostream &ost, const lint &number)
{
    ost << number.to_string();
    return ost;
}

// +
lint& lint::operator++ ()
{
    *this += 1;
    return *this;
}

// +
lint& lint::operator-- ()
{
    if (m_sign < 0)
    {
        char sign = m_sign;
        *this = abs(*this) + 1;
        m_sign = sign;
    }
    else
        *this -= 1;
    return *this;
}

// +
lint lint::operator++ (int)
{
    lint temp(*this);
    *this += 1;
    return temp;
}

// +
lint lint::operator-- (int)
{
    lint temp(*this);
    --*this;
    return temp;
}

// +
lint lint::operator+()
{
    return *this;
}

// +
lint lint::operator-()
{
    lint temp(*this);
    temp.m_sign *= -1;
    return temp;
}

// +
lint lint::operator+ (const lint &a)
{
    if (m_sign > 0 && a.m_sign > 0)
        return add(*this, a);
    if (m_sign < 0 && a.m_sign < 0)
    {
        lint temp = add(*this, a);
        temp.m_sign = -1;
        return temp;
    }
    if (*this < a)
    {
        if (abs(*this) > a)
        {
            lint b(abs(*this));
            b -= a;
            b.m_sign = -1;
            return b;
        }
        else
        {
            lint b(a);
            b -= abs(*this);
            b.m_sign = 1;
            return b;
        }
    }
    if (*this >= a)
    {
        if (*this > abs(a))
        {
            lint b(*this);
            b -= abs(a);
            b.m_sign = 1;
            return b;
        }
        else
        {
            lint b(abs(a));
            b -= *this;
            b.m_sign = -1;
            return b;
        }
    }
    return *this;
}

// positive a - positive b (a > b)
lint lint::operator- (const lint &a)
{
    lint temp(*this);    
    size_t carry = 0, i = 0;
    while (i < a.m_array.size() || carry)
    {
        temp.m_array[i] -= carry + (i < a.m_array.size() ? a.m_array[i] : 0);
        carry = temp.m_array[i] < 0;
        if (carry)
            temp.m_array[i] += m_base;
        ++i;
    }
    while (temp.m_array.size() > 1 && temp.m_array.back() == 0)
       temp.m_array.pop_back();
    return temp;
}

// +
lint lint::operator* (const lint &a)
{
    lint temp;
    temp.m_array.reserve(m_array.size() + a.m_array.size() + 1);
    int size = static_cast <int>(a.m_array.size());
    for(size_t i = 0; i < m_array.size(); ++i)
    {
        int j = 0, carry = 0;
        while (j < size || carry)
        {
            uint64_t current = temp.m_array[i + j] + m_array[i] * 1ll * (j < size ? a.m_array[j] : 0) + carry;
            temp.m_array[i + j] = current % m_base;
            carry = current / m_base;
            ++j;
        }
    }
    while (temp.m_array.size() > 1 && temp.m_array.back() == 0)
        temp.m_array.pop_back();
    temp.m_sign = m_sign * a.m_sign;
    return temp;
}

lint lint::operator/ (lint a)
{
    lint result, current;
    for(int i = m_array.size() - 1; i >= 0; --i)
    {
        current.level_up();
        current.m_array[0] = m_array[i];
        int value = 0, left = 0, right = m_base;
        while (left <= right)
        {
            int middle = (left + right) >> 1;
            lint cur = a * middle;
            if (cur <= current)
            {
                value = middle;
                left = middle + 1;
            }
            else
            {
                right = middle - 1;
            }
            result.m_array[i] = value;
            current = current - a * value;
        }
        int pos = m_array.size();
        while (pos >= 0 && !result.m_array[pos])
            --pos;
        result.m_array.push_back(0);
    }
    return result;
}

// +
lint lint::operator+ (int a)
{
    lint temp(*this);
    lint b(a);
    temp = temp + b;
    return temp;
}

lint lint::operator- (const int a)
{
    lint temp(*this);
    lint b(a);
    temp = temp - b;
    return temp;
}

// +
lint lint::operator* (const int a)
{
    lint temp(*this);
    lint b(a);
    temp = temp * b;
    return temp;
}

lint lint::operator/ (const int a)
{
    lint temp(a);
    return *this / temp;
}

// +
lint operator+ (const int a, const lint &b)
{
    lint temp(a);
    return temp + b;
}

// +
lint operator- (const int a, const lint &b)
{
    lint temp(a);
    return temp - b;
}

// +
lint operator* (const int a, const lint &b)
{
    lint temp(a);
    return temp * b;
}

// +
lint operator/ (const int a, const lint &b)
{
    lint temp(a);
    return temp / b;
}

lint& lint::operator += (const lint &number)
{
    *this = *this + number;
    return *this;
}

lint& lint::operator -= (const lint &number)
{
    *this = *this - number;
    return *this;
}

// +
lint& lint::operator *= (const lint &number)
{
    *this = *this * number;
    return *this;
}

lint& lint::operator /= (const lint &number)
{
    *this = *this / number;
    return *this;
}

lint& lint::operator+= (const int a)
{
    *this = *this + a;
    return *this;
}

lint& lint::operator-= (const int a)
{
    *this = *this - a;
    return *this;
}

lint& lint::operator*= (const int a)
{
    *this = *this * a;
    return *this;
}

lint& lint::operator/=(const int a)
{
    *this = *this / a;
    return *this;
}

// +
bool lint::operator< (lint number) const
{
    if (m_sign < number.m_sign)
        return true;

    if (m_sign > number.m_sign)
        return false;

    if (m_sign < 0 && number.m_sign < 0)
    {
        lint temp(*this);
        temp.m_sign = number.m_sign = 1;
        temp.swap(number);
        return temp < number;
    }

    if (m_array.size() < number.m_array.size())
        return true;
    if (m_array.size() > number.m_array.size())
        return false;

    int size = static_cast <int>(m_array.size());
    for(int i = size; i >= 0; --i)
    {
        if (m_array[i] < number.m_array[i])
            return true;
    }
    return false;
}

// +
bool lint::operator> (lint number) const
{
    return number < *this;
}

// +
bool lint::operator<= (lint number) const
{
    return *this < number || !(number < *this);
}

// +
bool lint::operator>= (lint number) const
{
    return number <= *this;
}

// +
bool lint::operator== (lint number) const
{
    if (m_array.size() != number.m_array.size())
        return false;
    return !(*this < number) && !(number < *this);
}

// +
bool lint::operator!= (lint number) const
{
    return !(*this == number);
}

bool lint::operator< (int number) const
{
    return false;
}

bool lint::operator> (int number) const
{
    return false;
}

bool lint::operator<= (int number) const
{
    return false;
}

bool lint::operator>= (int number) const
{
    return false;
}

bool lint::operator== (int number) const
{
    return false;
}

bool lint::operator!= (int number) const
{
    return false;
}

// +
lint abs(const lint &number)
{
    lint temp(number);
    temp.set_abs();
    return temp;
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

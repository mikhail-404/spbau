#include "lint.hpp"

lint::lint()
{

}

lint::lint(const lint &big_number)
{

}

lint& lint::operator=(const lint &big_number)
{
    return *this;
}

lint::~lint()
{

}

lint::lint(int int_number)
{

}

lint::lint(double doulbe_number)
{

}

lint::lint(const std::string &string_number)
{

}

lint::operator uint64_t()
{
    return 0;
}

lint::operator bool()
{
    return false;
}

std::string lint::to_string() const
{
    return "";
}

std::istream& operator>> (std::istream &ist, lint &number)
{
    return ist;
}

std::ostream& operator<< (std::ostream &ost, const lint &number)
{
    return ost;
}

lint& lint::operator++ ()
{
    return *this;
}

lint& lint::operator-- ()
{
    return *this;
}

lint& lint::operator++ (int)
{
    return *this;
}

lint& lint::operator-- (int)
{
    return *this;
}

lint lint::operator+ (const lint &a)
{
    lint temp(a);
    return temp;
}

lint lint::operator- (const lint &a)
{
    lint temp(a);
    return temp;
}

lint lint::operator* (const lint &a)
{
    lint temp(a);
    return temp;
}

lint lint::operator/ (const lint &a)
{
    lint temp(a);
    return temp;
}

lint& lint::operator += (const lint &number)
{
    return *this;
}

lint& lint::operator -= (const lint &number)
{
    return *this;
}

lint& lint::operator *= (const lint &number)
{
    return *this;
}

lint& lint::operator /= (const lint &number)
{
    return *this;
}

bool lint::operator<  (const lint &number) const
{
    return false;
}

bool lint::operator>  (const lint &number) const
{
    return number < *this;
}

bool lint::operator<= (const lint &number) const
{
    return number < *this || !(number < *this || *this < number);
}

bool lint::operator>= (const lint &number) const
{
    return number <= *this;
}

bool lint::operator== (const lint &number) const
{
    return !(*this < number && number < *this);
}

bool lint::operator!= (const lint &number) const
{
    return !(*this == number);
}

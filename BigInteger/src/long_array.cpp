#include "long_array.hpp"
#include <stdexcept>

typedef int mytype;

long_array::long_array()
    : m_array(new mytype [2]),
      m_capacity(2),
      m_size(0)
{
    fill_range(0, m_capacity);
}

long_array::long_array(size_t count)
    : m_array(new mytype [count]),
      m_capacity(count),
      m_size(0)
{
    fill_range(0, count);
}

long_array::long_array(mytype value, size_t count)
    : m_array(new mytype [count]),
      m_capacity(count),
      m_size(count)
{
    fill_range(value, count);
}

long_array::long_array(const long_array &array)
{
    m_capacity = array.m_capacity;
    m_size = array.m_size;
    m_array = new mytype [m_capacity];
    copy_array(m_array, array.m_array, m_size);
}


template <typename T>
void long_array::swap(T &a, T &b)
{
    T temp = a;
    a = b;
    b = temp;
}

void long_array::swap(long_array &array)
{
    swap(m_array, array.m_array);
    swap(m_capacity, array.m_capacity);
    swap(m_size, array.m_size);
}

void long_array::copy_array(mytype *dst, mytype *src, size_t count)
{
    for(size_t i = 0; i < count; ++i)
        dst[i] = src[i];
}

void long_array::fill_range(mytype value, size_t count)
{
    for(size_t i = 0; i < count; ++i)
        m_array[i] = value;
}

long_array& long_array::operator= (const long_array &array)
{
    long_array(array).swap(*this);
    return *this;
}

long_array::~long_array()
{
    delete []m_array;
}

void long_array::push_back(mytype value)
{
    if (m_size + 1 > m_capacity)
    {
        mytype *temp_array = new mytype [m_size];
        copy_array(temp_array, m_array, m_size);
        delete []m_array;
        m_capacity <<= 1;
        m_array = new mytype [m_capacity];
        copy_array(m_array, temp_array, m_size);
        delete []temp_array;
    }
    ++m_size;
    m_array[m_size - 1] = value;
}

void long_array::pop_back()
{
    if (m_size == 0)
        throw std::out_of_range("[long_array::pop_back] size = 0");
    --m_size;
}

mytype long_array::back() const
{
    if (m_size == 0)
        throw std::out_of_range("[long_array::back] size = 0");
    return m_array[m_size - 1];
}

mytype& long_array::operator[] (size_t index)
{
    if (index < 0 || index >= m_capacity)
        throw std::out_of_range("[long_array::operator[]] Out of range");
    return m_array[index];
}

const mytype& long_array::operator[](size_t index) const
{
    if (index < 0 || index >= m_capacity)
        throw std::out_of_range("[long_array::operator[]] Out of range");
    return m_array[index];
}

bool long_array::is_empty() const
{
    return m_size == 0;
}

size_t long_array::size() const
{
    return m_size;
}

void long_array::resize(const size_t size)
{
    for(int i = m_capacity; i <= size; ++i)
    {
        std::cout << i << std::endl;
        push_back(0);
    }
}

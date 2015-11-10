#ifndef LONG_ARRAY_HPP
#define LONG_ARRAY_HPP

#include <iostream>
#include <cstddef>

class long_array
{
public:
    //
    long_array();
    long_array(size_t count);
    long_array(uint32_t value, size_t count);
    long_array(const long_array &array);
    long_array& operator= (const long_array &array);
    ~long_array();
    //
    void push_back(int value);
    uint32_t back() const;
    void pop_back();
    uint32_t& operator[] (size_t index);
    const uint32_t& operator[] (size_t index) const;
    //
    bool is_empty() const;
    size_t size() const;
    //
    void reverse();
    //
private:
    //
    void swap(long_array &array);
    template <typename T> void swap(T &a, T &b);
    void copy_array(uint32_t *a, uint32_t *b, size_t count);
    void fill_range(int value, size_t count);
    //

private:
    uint32_t *m_array;
    size_t    m_capacity;
    size_t    m_size;
};

#endif // LONG_ARRAY_HPP

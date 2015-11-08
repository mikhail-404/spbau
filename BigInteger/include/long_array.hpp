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
    long_array(int value, size_t count);
    long_array(const long_array &array);
    long_array& operator= (const long_array &array);
    ~long_array();
    //
    void push_back(int value);
    int pop_back();
    int& operator[] (size_t index);
    //
    bool is_empty() const;
    size_t size() const;
    //
private:
    //
    void swap(long_array &array);
    template <typename T> void swap(T &a, T &b);
    void copy_array(int *a, int *b, size_t count);
    void fill_range(int value, size_t count);
    //

private:
    int   *m_array;
    size_t m_capacity;
    size_t m_size;
};

#endif // LONG_ARRAY_HPP

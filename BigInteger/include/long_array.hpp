#ifndef LONG_ARRAY_HPP
#define LONG_ARRAY_HPP

#include <iostream>
#include <cstddef>

typedef int mytype;

class long_array
{
public:
    //
    long_array();
    long_array(size_t count);
    long_array(mytype value, size_t count);
    long_array(const long_array &array);
    long_array& operator= (const long_array &array);
    ~long_array();
    //
    void push_back(mytype value);
    mytype back() const;
    void pop_back();
    mytype& operator[] (size_t index);
    const mytype& operator[] (size_t index) const;
    //
    bool is_empty() const;
    size_t size() const;
    //
    void resize(const size_t size);
    //
    void swap(long_array &array);

private:
    //    
    template <typename T>
    void swap(T &a, T &b);
    void copy_array(mytype *a, mytype *b, size_t count);
    void fill_range(mytype value, size_t count);
    //

private:
    mytype   *m_array;
    size_t    m_capacity;
    size_t    m_size;
};

#endif // LONG_ARRAY_HPP

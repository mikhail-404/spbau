#ifndef BINARY_HEAP_HPP
#define BINARY_HEAP_HPP

#include <vector>
#include <cstddef>

template <
        class T,
        class Container = std::vector <T>,
        class Comparator = std::less <typename Container::value_type>
> class BinaryHeap
{
public:
    //
    BinaryHeap();
    BinaryHeap(const Comparator &comp);
    //
    void insert(const T &value);
    void pop();
    //
    T top() const;
    //
    bool is_empty() const;
    size_t size () const;

private:
    //
    void sift_up(size_t index);
    void sift_down(size_t index);
    //
    size_t left_child (size_t index) const;
    size_t right_child(size_t index) const;
    size_t parent     (size_t index) const;

private:
    Container  m_data;
    Comparator m_comp;
    size_t     m_size;
};

template <class T, class Container, class Comparator>
BinaryHeap <T, Container, Comparator>::BinaryHeap()
    : m_size(0)
{
}

template <class T, class Container, class Comparator>
BinaryHeap <T, Container, Comparator>::BinaryHeap(const Comparator &comp)
    : m_comp(comp)
    , m_size(0)
{
}


template <class T, class Container, class Comparator>
void BinaryHeap <T, Container, Comparator>::insert(const T &value)
{
    m_data.push_back(value);
    ++m_size;
    sift_up(m_size - 1);
}


template <class T, class Container, class Comparator>
void BinaryHeap <T, Container, Comparator>::pop()
{
    std::swap(m_data[0], m_data[m_size - 1]);
    --m_size;
    sift_down(0);
}

template <class T, class Container, class Comparator>
T BinaryHeap <T, Container, Comparator>::top() const
{
    return m_data[0];
}

template <class T, class Container, class Comparator>
bool BinaryHeap <T, Container, Comparator>::is_empty() const
{
    return m_size == 0;
}

template <class T, class Container, class Comparator>
size_t BinaryHeap <T, Container, Comparator>::size() const
{
    return m_size;
}

template <class T, class Container, class Comparator>
size_t BinaryHeap <T, Container, Comparator>::left_child(size_t index) const
{
    return index * 2 + 1;
}

template <class T, class Container, class Comparator>
size_t BinaryHeap <T, Container, Comparator>::right_child(size_t index) const
{
    return index * 2 + 2;
}

template <class T, class Container, class Comparator>
size_t BinaryHeap <T, Container, Comparator>::parent(size_t index) const
{
    return index >> 1;
}

template <class T, class Container, class Comparator>
void BinaryHeap <T, Container, Comparator>::sift_up(size_t index)
{
    if (m_size == 0)
        return;

    size_t parent_id = parent(index);
    if (m_comp(m_data[parent_id], m_data[index]))
    {
        std::swap(m_data[parent_id], m_data[index]);
        sift_up(parent_id);
    }

}

template <class T, class Container, class Comparator>
void BinaryHeap <T, Container, Comparator>::sift_down(size_t index)
{
    size_t left  = left_child(index);
    size_t right = right_child(index);

    if (left >= m_size && right >= m_size)
        return;
    size_t min_id = index;
    if (left < m_size && right >= m_size)
        min_id = left;
    else
    {
        min_id = left;
        if (m_comp(m_data[left], m_data[right]))
            min_id = right;
    }
    std::swap(m_data[min_id], m_data[index]);
    sift_down(min_id);
}

#endif // BINARY_HEAP_HPP

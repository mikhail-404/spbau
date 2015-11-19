#include <iostream>
#include <ctime>
#include "binary_heap.hpp"

int main(int argc, char *argv[])
{
    BinaryHeap <int> heap;
    std::cout << "Random heap: ";
    for(int i = 10; i > 0; --i)
    {
        int random_value = std::rand() % 100;
        std::cout << " " << random_value;
        heap.insert(random_value);
    }

    std::cout << "\nHeap sort sequence: ";
    while (!heap.is_empty())
    {
        std::cout << " " << heap.top();
        heap.pop();
    }

    return 0;
}

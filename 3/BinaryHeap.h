#include <iostream>
#include <algorithm>
#include <vector>

#define ROOT 1
#define LEFT(n) ((n) << 1)
#define RIGHT(n) (((n) << 1) | 1)
#define PARENT(n) ((n) >> 1)
#define COMPARE(a, b) ((a) > (b)) // a>b for min heap, a<b for max heap

using namespace std;

template <typename T>
void swap_elem(T *a, T *b)
{
    T temp = *a;
    *a = *b;
    *b = temp;
}

template <typename T>
class BinaryHeap
{
public:
    BinaryHeap()
    {
        array.push_back(static_cast<T>(NULL));
        size = array.size() - 1;
    }
    BinaryHeap(const vector<T> &_array)
    {
        array.push_back(static_cast<T>(NULL));
        for (auto _it = _array.begin(); _it != _array.end(); _it++)
            array.push_back(*_it);
        size = array.size() - 1;
        buildHeap();
    }
    ~BinaryHeap() { array.clear(); }
    const T root() { return array[ROOT]; }
    bool isEmpty() const { return size == 0; }
    void insert(const T &x);
    void deleteRoot();
    void makeEmpty();

private:
    /* data */
    vector<T> array;
    int size;
    void buildHeap();
    void percolateDown(int hole);
};

template <typename T>
void BinaryHeap<T>::insert(const T &x)
{
    int hole = ++size;
    // percolate Up
    array.push_back(static_cast<T>(NULL));
    for (; hole != 1 && COMPARE(array[PARENT(hole)], x); hole = PARENT(hole))
    {
        array[hole] = move(array[PARENT(hole)]);
    }
    array[hole] = move(x);
}

template <typename T>
void BinaryHeap<T>::deleteRoot()
{
    if (isEmpty())
        return;
    array[ROOT] = array.back();
    array.pop_back();
    size--;
    percolateDown(ROOT);
}

template <typename T>
void BinaryHeap<T>::makeEmpty()
{
    array.clear();
    array.push_back(static_cast<T>(NULL));
    size = 0;
}

template <typename T>
void BinaryHeap<T>::buildHeap()
{
    for (int i = PARENT(size); i > 0; i--)
        percolateDown(i);
}

template <typename T>
void BinaryHeap<T>::percolateDown(int hole)
{
    int child = LEFT(hole);
    for (; LEFT(hole) <= size; hole = child)
    {
        child = LEFT(hole);
        if (RIGHT(hole) <= size && COMPARE(array[LEFT(hole)], array[RIGHT(hole)]))
            child += 1;
        if (COMPARE(array[hole], array[child]))
        {
            swap_elem(&(array[hole]), &(array[child]));
            // percolateDown(child);
        }
        else // heapify end;
            break;
    }
    return;
}

// template <typename T>
// void BinaryHeap<T>::percolateDown(int hole)
// {
//     bool left = LEFT(hole) <= size;
//     bool right = RIGHT(hole) <= size;
//     if (!left && !right)
//     {
//     }
//     else if (!right)
//     {
//         if (COMPARE(array[hole], array[LEFT(hole)]))
//         {
//             swap_elem(&(array[hole]), &(array[LEFT(hole)]));
//             percolateDown(LEFT(hole));
//         }
//     }
//     else if (left && right && COMPARE(array[RIGHT(hole)], array[LEFT(hole)]))
//     {
//         if (COMPARE(array[hole], array[LEFT(hole)]))
//         {
//             swap_elem(&(array[hole]), &(array[LEFT(hole)]));
//             percolateDown(LEFT(hole));
//         }
//     }
//     else // left && right && !compare(RIGHT, LEFT)
//     {
//         if (COMPARE(array[hole], array[RIGHT(hole)]))
//         {
//             swap_elem(&(array[hole]), &(array[RIGHT(hole)]));
//             percolateDown(RIGHT(hole));
//         }
//     }
//     return;
// }
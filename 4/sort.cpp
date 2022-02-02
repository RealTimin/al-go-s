#include <iostream>
#include <vector>
#include <queue>

#define EXP 8
#define RADIX (1 << EXP)
using namespace std;

template <typename T>
void swap_elem(T *a, T *b)
{
    T temp = *a;
    *a = *b;
    *b = temp;
} // instead, you can use std::swap(T &a, T &b) which is in <algorithm>

template <typename T>
void insertionSort(vector<T> &v, int si, int ei)
{
    for (int i = si + 1; i <= ei; i++)
    {
        for (int j = i; j > si && v[j] < v[j - 1]; j--)
        {
            swap_elem(&(v[j]), &(v[j - 1]));
        }
    }
}

template <typename T>
void insertionSort(vector<T> &v)
{
    insertionSort(v, 0, v.size() - 1);
}

// template <class T>
// void percolateDown(vector<T> &v, int size, int index)
// {
//     int i = index;
//     int child = 2 * i + 1; // left child
//     // make max heap
//     for (; child < size; i = child)
//     {
//         if (child + 1 < size && v[child] < v[child + 1])
//             child++;
//         if (v[i] < v[child])
//             swap_elem(&(v[i]), &(v[child]));
//         else
//             break;
//     }
//     return;
// }

// template <class T>
// void heapSort(vector<T> &v)
// {
//     int s = v.size();
//     // heapify
//     for (int i = s / 2 - 1; i >= 0; i--)
//         percolateDown(v, s, i);

//     // heapSort
//     for (int i = s - 1; i > 0; i--)
//     {
//         swap_elem(&(v[0]), &(v[i]));
//         s--;
//         percolateDown(v, s, 0);
//     }

//     return;
// }

template <class T>
void percolateDown(vector<T> &v, int index, int si, int ei) // for introSort, add parameter si, ei -> heapsort for si~ei
{
    // si + index: position to start percolate down
    int size = ei - si + 1;
    int i = index;
    int child = 2 * i + 1; // left child
    // make max heap
    for (; child < size; i = child)
    {
        if (child + 1 < size && v[si + child] < v[si + child + 1])
            child++; // right child
        if (v[si + i] < v[si + child])
            swap_elem(&(v[si + i]), &(v[si + child]));
        else
            break;
    }
    return;
}

template <class T>
void heapSort(vector<T> &v, int si, int ei) // for introSort, add parameter si, ei -> heapsort for si~ei
{
    int s = ei - si + 1;
    // heapify
    for (int i = s / 2 - 1; i >= 0; i--)
        percolateDown(v, i, si, ei);

    // heapSort
    for (int i = s - 1; i > 0; i--)
    {
        swap_elem(&(v[si]), &(v[si + i]));
        s--;
        percolateDown(v, 0, si, si + s);
    }

    return;
}

template <class T>
void heapSort(vector<T> &v)
{
    heapSort(v, 0, v.size() - 1);
}

template <class T>
void mergeSort(vector<T> &v, int si, int ei, T *arr)
{
    if (ei - si < 10)
    {
        insertionSort(v, si, ei);
    }
    else
    {
        // mergeSort

        if (ei == si)
            return;
        int mid = si + (ei - si) / 2;
        // divide into two arrays
        mergeSort(v, si, mid, arr);
        mergeSort(v, mid + 1, ei, arr);
        // merge two arrays
        int i = si;
        int j = mid + 1;
        for (int k = si; k <= ei; k++)
        {
            if (i == mid + 1)
                arr[k] = v[j++];
            else if (j == ei + 1)
                arr[k] = v[i++];
            else if (v[i] > v[j]) // be careful about '=', otherwise not stable sort
                arr[k] = v[j++];
            else
                arr[k] = v[i++];
        }

        for (int k = si; k <= ei; k++)
            v[k] = arr[k];
    }
    return;
}

template <class T>
void mergeSort(vector<T> &v)
{
    T *arr = new T[v.size()];
    mergeSort(v, 0, v.size() - 1, arr);
    delete[] arr;
}

template <class T>
void quickSort(vector<T> &v, int si, int ei)
{
    if (ei - si + 1 < 10)
    {
        insertionSort(v, si, ei);
    }
    else
    {
        // quickSort
        if (si >= ei)
            return;

        int mid = si + (ei - si) / 2;
        // median of 3 method, bubbleSort
        if (v[si] > v[mid])
            swap_elem(&(v[si]), &(v[mid]));
        if (v[mid] > v[ei])
            swap_elem(&(v[mid]), &(v[ei]));
        if (v[si] > v[mid])
            swap_elem(&(v[si]), &(v[mid]));

        // if the size is greater than 3, need more sort
        if (ei - si + 1 > 3)
        {
            int pivot = si + 1;
            int i = pivot;
            int j = ei;

            // move pivot(=median of 3) to (si+1) th position
            swap_elem(&(v[pivot]), &(v[mid]));
            // swap element based on pivot value
            while (i < j)
            {
                while (++i < ei && v[i] < v[pivot])
                    ; // range of i: pivot + 1 <= i <= ei
                while (--j > pivot && v[j] > v[pivot])
                    ; // range of j: pivot <= j <= ei - 1
                if (i < j)
                {
                    swap_elem(&(v[i]), &(v[j]));
                }
            }
            // move pivot to (i-1) th position (si+1 <= i-1 <= ei-1)
            swap_elem(&(v[pivot]), &(v[i - 1]));
            mid = i - 1;
        }

        // if (mid - si > 1)
        quickSort(v, si, mid - 1);
        // if (ei - mid > 1)
        quickSort(v, mid + 1, ei);
    }
    return;
}

template <class T>
void quickSort(vector<T> &v)
{
    quickSort(v, 0, v.size() - 1);
}

void radixSort(vector<unsigned int> &v)
{
    // RADIX = (1 << UNIT)
    vector<queue<unsigned int>> r(RADIX);
    unsigned int placeValue;
    // cout << r.size();
    for (int i = 0; EXP * i < 32; i++)
    {
        for (auto it = v.begin(); it != v.end(); it++)
        {
            placeValue = ((*it) >> (EXP * i)) & (RADIX - 1);
            r[placeValue].push(*it);
        }

        auto it = v.begin();
        for (int j = 0; j < RADIX && it != v.end(); j++)
        {
            while (!r[j].empty())
            {
                (*it) = r[j].front();
                it++;
                r[j].pop();
            }
        }
    }

    return;
}

int main()
{
    vector<unsigned int> v = {3, 1, 5, 7, 7, 3, 1, 3, 1, 6, 2};
    // vector<unsigned int> v = {12351, 3146236, 1241234, 245356, 12341234, 4573573, 1311345, 24624, 23452452};
    // insertionSort(v);
    heapSort(v);
    // mergeSort(v);
    // quickSort(v);
    // radixSort(v);

    // print
    for (auto it = v.begin(); it != v.end(); it++)
        cout << (*it) << ' ';
    return 0;
}

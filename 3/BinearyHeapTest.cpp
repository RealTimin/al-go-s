#include <iostream>
#include <algorithm>
#include "BinaryHeap.h"

using namespace std;

int main()
{
    BinaryHeap<int> bh;
    cout << bh.isEmpty() << endl;
    bh.insert(3);
    bh.insert(2);
    bh.insert(1);
    bh.insert(5);
    bh.insert(6);
    bh.insert(7);
    cout << bh.isEmpty() << endl;

    bh.deleteRoot();
    bh.deleteRoot();
    bh.deleteRoot();

    bh.makeEmpty();
    cout << bh.isEmpty() << endl;

    
    return 0;
}
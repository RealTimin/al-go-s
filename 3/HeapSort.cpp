#include <iostream>
#include <algorithm>
#include "BinaryHeap.h"

using namespace std;

int main()
{
    vector<int> v = {3, 5, 1, 6, 7, 2, 5, 8, 3, 2, 2};
    BinaryHeap<int> bh(v);
    v.clear();
    while (!bh.isEmpty())
    {
        v.push_back(bh.root());
        bh.deleteRoot();
    }

    for (auto it = v.begin(); it != v.end(); it++)
        cout << *it << ' ';
    cout << endl;
    return 0;
}

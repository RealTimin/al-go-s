#include <iostream>
#include <algorithm>
#include "SimpleTree.h"
using namespace std;

int main()
{
    SimpleTree<int> tr(5);
    tr.attach(3);
    tr.attach(2);
    tr.attach(1);
    tr.get_child(1)->attach(5);
    tr.get_child(1)->attach(4);
    tr.get_child(2)->attach(3);
    tr.get_child(2)->get_child(1)->attach(2);

    tr.BFS_print();
    tr.DFS_print();

    cout << tr.height() << endl;
    cout << tr.size() << endl;
    cout << tr.get_child(2)->get_child(1)->get_child(1)->depth() << endl;
    return 0;
}
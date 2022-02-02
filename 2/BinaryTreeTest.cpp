#include <iostream>
#include <algorithm>
#include "BinarySearchTree.h"

using namespace std;

int main()
{
    BinarySearchTree<int> bst;
    cout << bst.isEmpty() << endl;
    bst.insert(3);
    bst.insert(2);
    bst.insert(5);
    bst.insert(4);
    bst.insert(7);
    bst.insert(1);
    bst.printTree();
    cout << endl;

    bst.printTree_preorder();
    // cout << bst.contains(7) << ' ' << bst.contains(8) << endl;

    bst.remove(3);
    bst.remove(7);
    bst.printTree();
    cout << endl;

    bst.makeEmpty();
    bst.printTree();
    bst.insert(1);
    bst.printTree();

    return 0;
}
#include <iostream>
#include <algorithm>
#include <vector>
#include <list>

using namespace std;

int main()
{
    vector<int> v;
    list<int> l;
    l.push_back(3);
    auto it = l.begin();
    cout << *++it << endl;
    cout << *l.end() << endl;

    return 0;
}
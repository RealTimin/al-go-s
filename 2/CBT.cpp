#include <iostream>
#include <algorithm>
#include <vector>
#include <list>

#define LEFT(n) ((n) << 1)
#define RIGHT(n) ((n) << 1 | 1)
#define PARENT(n) ((n) >> 1)

using namespace std;

int main()
{
    vector<int> cbt(1, 0);
    cbt.push_back(1);
    cbt.push_back(2);
    cbt.push_back(3);
    cbt.push_back(4);
    cbt.push_back(5);
    cbt.push_back(6);
    cbt.push_back(7);
    cbt.push_back(8);
    int idx = 1; // root index
    cbt[(LEFT(idx))] = 3;
    cbt[RIGHT(LEFT(idx))] = 1;

    for (auto it = cbt.begin(); it != cbt.end(); it++)
    {
        cout << (*it) << ' ';
    }
    return 0;
}
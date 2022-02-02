#include <iostream>
#include <vector>

#define REP(i, a, b) for (int i = (a); i < (b); i++)

using namespace std;

class UnionFind
{
public:
    UnionFind() : size(0){};
    UnionFind(int _size)
    {
        size = _size;
        parent.assign(size, 0);
        rank.assign(size, 0);
        MakeAllSet();
    }
    int GetSize() { return size; }
    void Resize(int _size)
    {
        parent.resize(_size);
        rank.resize(_size);
        REP(i, size, _size)
        {
            MakeSet(i);
        }
    }

    void MakeAllSet();
    void MakeSet(int x);
    int Find(int x);
    void Union(int x, int y);

private:
    int size;
    vector<int> parent;
    vector<int> rank;
};

void UnionFind::MakeAllSet()
{
    REP(i, 0, size)
    {
        MakeSet(i);
    }
}
void UnionFind::MakeSet(int x)
{
    if (x < 0 || x >= size)
        return;
    parent[x] = x;
    rank[x] = 0;
}
int UnionFind::Find(int x)
{
    if (x < 0 || x >= size)
        return -1;
    if (parent[x] == x)
        return x;
    parent[x] = Find(parent[x]);
    return parent[x];
}
void UnionFind::Union(int x, int y)
{
    if (x < 0 || x >= size)
        return;
    if (y < 0 || y >= size)
        return;
    int px = Find(x);
    int py = Find(y);
    if (px == py)
        return;
    int si = px > py ? py : px;
    int bi = px > py ? px : py;
    if (rank[si] < rank[bi])
    {
        parent[si] = bi;
    }
    else
    {
        parent[bi] = si;
        if (rank[si] == rank[bi])
            rank[si]++;
    }
}

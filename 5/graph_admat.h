#include <iostream>
#include <algorithm>
#include <vector>
#include <list>
#include <queue>
#include <string>

using namespace std;

class Graph_admat
{

public:
    Graph_admat() : nodeCount(0), edgeCount(0), directed(false) { matrix.clear(); }
    Graph_admat(int _nc, bool _d = false) : nodeCount(_nc), edgeCount(0), directed(_d)
    {
        matrix.clear();
        for (int i = 0; i < nodeCount; i++)
        {
            matrix.push_back(vector<int>(nodeCount, 0));
        }
    }

    int GetNodeCount() const { return nodeCount; }
    int GetEdgeCount() const { return edgeCount; }
    void InsertNode();            // add 1 more node
    void InsertNode(int newSize); // increase matrix size to newSize.
    void InsertEdge(int i1, int i2);
    void BFS(int startIndex);
    void DFS(int startIndex);

    bool isConnected(int i1, int i2);

private:
    void DFSTraversal(bool *visited, int index);
    vector<vector<int>> matrix; // HACK: is this alright? matrix_ij: edge count from j to i
    bool directed;
    int nodeCount;
    int edgeCount;
};

void Graph_admat::InsertNode()
{
    InsertNode(nodeCount + 1);
}

void Graph_admat::InsertNode(int newSize)
{
    int size = matrix.size();
    if (newSize >= 0 && newSize > size)
    {
        for (int i = 0; i < size; i++)
        {
            matrix[i].resize(newSize);
        }
        for (int i = size; i < newSize; i++)
        {
            matrix.push_back(vector<int>(newSize, 0));
        }
        nodeCount = newSize;
    }
    return;
}

void Graph_admat::InsertEdge(int i1, int i2)
{
    InsertNode(i1);
    InsertNode(i2);
    if (i1 >= 0 && i2 >= 0)
    {
        if (directed)
        {
            matrix[i2][i1]++;
            edgeCount++;
        }
        else
        {
            matrix[i2][i1]++;
            matrix[i1][i2]++;
            edgeCount += 2;
        }
    }
}

void Graph_admat::BFS(int startIndex)
{
    bool *visited = new bool[nodeCount];
    queue<int> d;
    int index;

    for (int i = 0; i < nodeCount; i++)
        visited[i] = false;
    if (startIndex >= 0 && startIndex < nodeCount)
        d.push(startIndex);
    while (!d.empty())
    {
        index = d.front();
        if (!visited[index])
        {
            cout << index << ' ';
            for (int i = 0; i < nodeCount; i++)
            {
                if (matrix[i][index] > 0)
                    d.push(i);
            }
            visited[index] = true;
        }
        d.pop();
    }
    delete[] visited;
    return;
}

void Graph_admat::DFS(int startIndex)
{
    bool *visited = new bool[nodeCount];
    for (int i = 0; i < nodeCount; i++)
        visited[i] = false;
    if (startIndex >= 0 && startIndex < nodeCount)
        DFSTraversal(visited, startIndex);
    delete[] visited;
    return;
}

void Graph_admat::DFSTraversal(bool *visited, int index)
{
    visited[index] = true;
    cout << index << ' ';
    int ni;
    for (int i = 0; i < nodeCount; i++)
    {
        if (visited[i] == false)
            DFSTraversal(visited, i);
    }
    return;
}
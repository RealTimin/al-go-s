#include <iostream>
#include "graph.h"

using namespace std;

int main()
{
    // Graph g(5);
    // g.InsertEdge(0, 3);
    // g.InsertEdge(0, 2);
    // g.InsertEdge(0, 1);
    // g.InsertEdge(0, 4);
    // g.InsertEdge(2, 3);
    // g.InsertEdge(4, 3);
    // g.InsertEdge(0, 3);
    // g.DFS(0);
    // g.BFS(0);

    // Graph g(4);
    // g.InsertEdge(0, 1);
    // g.InsertEdge(0, 2);
    // g.InsertEdge(1, 2);
    // g.InsertEdge(2, 3);
    // cout << g.hasCycle() << endl;

    Graph g(7);
    g.InsertEdge(0, 1);
    g.InsertEdge(0, 4);
    g.InsertEdge(0, 5);
    g.InsertEdge(1, 2);
    g.InsertEdge(1, 3);
    g.InsertEdge(1, 4);
    g.InsertEdge(1, 5);
    g.InsertEdge(2, 3);
    g.InsertEdge(3, 4);
    g.InsertEdge(3, 5);
    g.InsertEdge(3, 6);
    g.InsertEdge(4, 6);
    g.hasCycle();

    // Graph f(4, true);
    // f.InsertEdge(0, 1);
    // f.InsertEdge(0, 2);
    // f.InsertEdge(1, 2);
    // f.InsertEdge(2, 0);
    // f.InsertEdge(2, 3);
    // f.InsertEdge(3, 3);
    // cout << f.hasCycle() << endl;

    return 0;
}
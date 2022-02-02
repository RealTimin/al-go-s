#include <iostream>

#include "graph.h"

int main()
{
    Graph g(6, true);
    g.InsertEdge(0, 1);
    g.InsertEdge(1, 2);
    g.InsertEdge(2, 3);
    g.InsertEdge(3, 1);
    g.InsertEdge(0, 4);
    g.InsertEdge(4, 5);
    g.InsertEdge(5, 4);
    g.InsertEdge(5, 3);

    // g.InsertEdge(1, 0);

    g.Kosaraju();
    g.Tarjan();
}
#include <iostream>

#include "weightedGraph.h"

int main()
{
    // WeightedGraph g(4, true);
    // g.InsertEdge(0, 1, 2);
    // g.InsertEdge(0, 2, 5);
    // g.InsertEdge(1, 2, 1);
    // g.InsertEdge(1, 3, 4);
    // g.InsertEdge(2, 3, 3);
    // cout << g.FordFulkerson(0, 3);

    WeightedGraph g(6, true);
    g.InsertEdge(0, 1, 7);
    g.InsertEdge(0, 3, 5);
    g.InsertEdge(1, 3, 5);
    g.InsertEdge(1, 2, 3);
    g.InsertEdge(2, 3, 2);
    g.InsertEdge(3, 4, 9);
    g.InsertEdge(4, 2, 2);
    g.InsertEdge(2, 5, 6);
    g.InsertEdge(4, 5, 4);

    cout << g.FordFulkerson(0, 5);
    return 0;
}
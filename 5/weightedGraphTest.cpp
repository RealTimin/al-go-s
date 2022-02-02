#include <iostream>
#include "weightedGraph.h"

using namespace std;

int main()
{
    WeightedGraph g(7);
    g.InsertEdge(0, 1, 7);
    g.InsertEdge(0, 4, 3);
    g.InsertEdge(0, 5, 10);
    g.InsertEdge(1, 2, 4);
    g.InsertEdge(1, 3, 10);
    g.InsertEdge(1, 4, 2);
    g.InsertEdge(1, 5, 6);
    g.InsertEdge(2, 3, 2);
    g.InsertEdge(3, 4, 11);
    g.InsertEdge(3, 5, 9);
    g.InsertEdge(3, 6, 4);
    g.InsertEdge(4, 6, 5);

    // cout << g.GetEdgeCount() << endl;

    // g.Dijkstra(0);
    // g.Dijkstra_pq(0);

    // g.Prim(0);
    // g.Prim_pq(0);

    // g.Kruskal();

    g.BellmanFord(0);
    g.FloydWarshall();
    return 0;
}
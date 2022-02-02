#include <iostream>
#include "graph.h"

using namespace std;

int main()
{
    Graph g(3);
    cout << g.isBipartite() << endl;
    g.InsertEdge(0, 1);
    g.InsertEdge(2, 1);
    g.InsertEdge(0, 2);
    cout << g.isBipartite() << endl;

    Graph f(4);
    f.InsertEdge(0, 2);
    f.InsertEdge(0, 3);
    f.InsertEdge(1, 2);
    f.InsertEdge(1, 3);
    cout << f.isBipartite() << endl;
    return 0;
}
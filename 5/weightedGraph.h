#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <algorithm>
#include "UnionFind.h"

#define INF __INT_MAX__

using namespace std;

class Node
{
public:
    Node(int _index) : index(_index) { anodes.clear(); }
    ~Node() { anodes.clear(); }
    int index;
    list<pair<Node *, int>> anodes; // first: adjacent node, second: edge weight
};

class WeightedEdge
{
public:
    WeightedEdge(int s, int e, int w) : start(s), end(e), weight(w){};
    int start;
    int end;
    int weight;
};

class WeightedGraph
{
public:
    WeightedGraph() : nodeCount(0), edgeCount(0), directed(false) { nodes.clear(); }
    WeightedGraph(int _nc, bool _d = false) : nodeCount(_nc), edgeCount(0), directed(_d)
    {
        nodes.clear();
        for (int i = 0; i < nodeCount; i++)
        {
            Node *newNode = new Node(i);
            nodes.push_back(newNode);
        }
    }

    ~WeightedGraph()
    {
        for (auto it = nodes.begin(); it != nodes.end(); it++)
        {
            if (*it)
            {
                delete (*it);
                (*it) = nullptr;
            }
        }
        nodes.clear();
        edges.clear();
    }

    int GetNodeCount() const { return nodeCount; }
    int GetEdgeCount() const { return edgeCount; }
    void InsertNode();
    void InsertNode(int index);
    void InsertEdge(int i1, int i2, int weight);
    void BFS(int startIndex);
    void DFS(int startIndex);
    bool isConnected(int i1, int i2) { return false; }

    void Dijkstra(int startIndex);
    void Dijkstra_pq(int startIndex);

    void Prim(int startIndex);
    void Prim_pq(int startIndex);

    void Kruskal();

    bool BellmanFord(int startIndex);

    bool FloydWarshall();

    int FordFulkerson(int source, int sink);

private:
    vector<Node *> nodes;
    vector<WeightedEdge> edges;
    bool directed;
    int nodeCount;
    int edgeCount;
    void DFSTraversal(bool *visited, int index);
    int FF_DFS(int index, int sink, vector<vector<int>> &res, int *parent);
};

void WeightedGraph::InsertNode()
{
    int index;
    for (index = 0; index < nodes.size() && nodes[index] != nullptr; index++)
        ;
    InsertNode(index);
}

void WeightedGraph::InsertNode(int index)
{
    if (nodes.size() < index + 1)
        nodes.resize(index + 1);
    if (index >= 0 && nodes[index] == nullptr)
    {
        Node *newNode = new Node(index);
        nodes[index] = newNode;
        nodeCount++;
    }
    return;
}

void WeightedGraph::InsertEdge(int i1, int i2, int weight)
{
    InsertNode(i1);
    InsertNode(i2);
    if (i1 >= 0 && i2 >= 0)
    {
        if (directed)
        {
            nodes[i1]->anodes.push_back(pair<Node *, int>(nodes[i2], weight));
            edges.push_back(WeightedEdge(i1, i2, weight));
            edgeCount++;
        }
        else
        {
            nodes[i2]->anodes.push_back(pair<Node *, int>(nodes[i1], weight));
            nodes[i1]->anodes.push_back(pair<Node *, int>(nodes[i2], weight));
            edges.push_back(WeightedEdge(i1, i2, weight));
            edges.push_back(WeightedEdge(i2, i1, weight));
            edgeCount++;
        }
    }
}

void WeightedGraph::BFS(int startIndex)
{
    bool *visited = new bool[nodes.size()];
    queue<Node *> d;
    int index;

    for (int i = 0; i < nodes.size(); i++)
        visited[i] = false;
    if (startIndex >= 0 && startIndex < nodes.size() && nodes[startIndex] != nullptr)
        d.push(nodes[startIndex]);
    while (!d.empty())
    {
        index = d.front()->index;
        if (!visited[index])
        {
            cout << nodes[index]->index << ' ';
            for (auto it = nodes[index]->anodes.begin(); it != nodes[index]->anodes.end(); it++)
            {
                d.push((*it).first);
            }
            visited[index] = true;
        }
        d.pop();
    }
    delete[] visited;
    return;
}

void WeightedGraph::DFS(int startIndex)
{
    bool *visited = new bool[nodes.size()];
    for (int i = 0; i < nodes.size(); i++)
        visited[i] = false;
    if (startIndex >= 0 && startIndex < nodes.size() && nodes[startIndex] != nullptr)
        DFSTraversal(visited, startIndex);
    delete[] visited;
    return;
}

void WeightedGraph::DFSTraversal(bool *visited, int index)
{
    visited[index] = true;
    cout << nodes[index]->index << ' ';
    int ni;
    for (auto it = nodes[index]->anodes.begin(); it != nodes[index]->anodes.end(); it++)
    {
        ni = (*it).first->index;
        if (visited[ni] == false)
            DFSTraversal(visited, ni);
    }
    return;
}

void WeightedGraph::Dijkstra(int startIndex)
{
    struct NodeInfo
    {
        /* data */
        // int index;
        int distance = INF;
        bool visited = false;
        Node *prevNode = nullptr;
    };

    int min_distance;
    int min_index = 0;
    bool min_found;
    int neighbor_index;
    int size = nodes.size();
    NodeInfo *nodeInfo = new NodeInfo[size];

    if (startIndex >= 0 && startIndex < size && nodes[startIndex] != nullptr)
    {
        nodeInfo[startIndex].distance = 0;
    }

    while (1)
    {
        // find unvisited, min distance node N. if all unvisited node is infinity distance, stop loop.

        min_distance = INF;
        min_index = 0;
        min_found = false;
        for (int i = 0; i < size; i++)
        {
            if (nodes[i] != nullptr && !nodeInfo[i].visited && nodeInfo[i].distance < min_distance)
            {
                min_distance = nodeInfo[i].distance;
                min_index = i;
                min_found = true;
            }
        }
        if (!min_found)
            break;

        // update N's neighbor
        // if N's neighbor is unvisited & distance is smaller, distance update & prevNode update
        for (auto it = nodes[min_index]->anodes.begin(); it != nodes[min_index]->anodes.end(); it++)
        {
            neighbor_index = (*it).first->index;
            if (nodes[neighbor_index] != nullptr && !nodeInfo[neighbor_index].visited && min_distance + (*it).second < nodeInfo[neighbor_index].distance)
            {
                nodeInfo[neighbor_index].distance = min_distance + (*it).second;
                nodeInfo[neighbor_index].prevNode = nodes[min_index];
            }
        }
        // N is visited
        nodeInfo[min_index].visited = true;
    }

    // print nodeInfo
    Node *prevNode = nullptr;
    for (int i = 0; i < size; i++)
    {
        if (nodes[i] != nullptr)
        {
            cout << "Node " << i;
            cout << " - visited: " << nodeInfo[i].visited << ", distance from Node " << startIndex << ": " << nodeInfo[i].distance << endl;
            cout << "path from Node " << i << " to " << startIndex << ": " << i;
            prevNode = nodeInfo[i].prevNode;
            while (prevNode != nullptr)
            {
                cout << " -> " << prevNode->index;
                prevNode = nodeInfo[prevNode->index].prevNode;
            }
            cout << endl;
        }
    }
    delete[] nodeInfo;
    return;
}

void WeightedGraph::Dijkstra_pq(int startIndex)
{
    struct NodeInfo
    {
        /* data */
        int index;
        int distance = INF;
        bool visited = false;
        Node *prevNode = nullptr;
    };
    struct compare
    {
        bool operator()(NodeInfo n1, NodeInfo n2)
        {
            return n1.distance > n2.distance; // greater -> min heap
        }
    };
    int min_distance;
    int min_index;
    Node *min_prevNode;
    int neighbor_index;
    int size = nodes.size();
    NodeInfo *nodeInfo = new NodeInfo[size];

    priority_queue<NodeInfo, vector<NodeInfo>, compare> pq;

    if (startIndex >= 0 && startIndex < size && nodes[startIndex] != nullptr)
    {
        nodeInfo[startIndex].distance = 0;
    }

    for (int i = 0; i < size; i++)
    {
        nodeInfo[i].index = i;
        if (nodes[i] != nullptr)
            pq.push(nodeInfo[i]);
    }

    while (1)
    {
        // find unvisited, min distance node N.
        // if all unvisited node is infinity distance, stop loop.
        if (pq.empty())
            break;
        min_distance = pq.top().distance;
        min_index = pq.top().index;
        min_prevNode = pq.top().prevNode;
        pq.pop();
        if (min_distance == INF)
            break;
        // if N is not visited, update nodeInfo. else erase
        if (!nodeInfo[min_index].visited)
        {
            nodeInfo[min_index].distance = min_distance;
            nodeInfo[min_index].prevNode = min_prevNode;
            nodeInfo[min_index].visited = true;
        }
        else
            continue;

        // update N's neighbor
        // if N's neighbor is unvisited & distance is smaller, distance update & prevNode update
        for (auto it = nodes[min_index]->anodes.begin(); it != nodes[min_index]->anodes.end(); it++)
        {
            neighbor_index = (*it).first->index;
            if (nodes[neighbor_index] != nullptr && !nodeInfo[neighbor_index].visited && min_distance + (*it).second < nodeInfo[neighbor_index].distance)
            {
                nodeInfo[neighbor_index].distance = min_distance + (*it).second;
                nodeInfo[neighbor_index].prevNode = nodes[min_index];
                pq.push(nodeInfo[neighbor_index]);
            }
        }
    }

    // print nodeInfo
    Node *prevNode = nullptr;
    for (int i = 0; i < size; i++)
    {
        if (nodes[i] != nullptr)
        {
            cout << "Node " << i;
            cout << " - visited: " << nodeInfo[i].visited << ", distance from Node " << startIndex << ": " << nodeInfo[i].distance << endl;
            cout << "path from Node " << i << " to " << startIndex << ": " << i;
            prevNode = nodeInfo[i].prevNode;
            while (prevNode != nullptr)
            {
                cout << " -> " << prevNode->index;
                prevNode = nodeInfo[prevNode->index].prevNode;
            }
            cout << endl;
        }
    }
    delete[] nodeInfo;
    return;
}

void WeightedGraph::Prim(int startIndex)
{
    struct NodeInfo
    {
        /* data */
        // int index;
        int distance = INF;
        bool visited = false;
        Node *prevNode = nullptr;
    };

    int min_distance;
    int min_index = 0;
    bool min_found;
    int neighbor_index;
    int size = nodes.size();
    NodeInfo *nodeInfo = new NodeInfo[size];

    if (startIndex >= 0 && startIndex < size && nodes[startIndex] != nullptr)
    {
        nodeInfo[startIndex].distance = 0;
    }

    while (1)
    {
        // find unvisited, min distance node N. if all unvisited node is infinity distance, stop loop.

        min_distance = INF;
        min_index = 0;
        min_found = false;
        for (int i = 0; i < size; i++)
        {
            if (nodes[i] != nullptr && !nodeInfo[i].visited && nodeInfo[i].distance < min_distance)
            {
                min_distance = nodeInfo[i].distance;
                min_index = i;
                min_found = true;
            }
        }
        if (!min_found)
            break;

        // N is visited
        nodeInfo[min_index].visited = true;

        // update N's neighbor
        // if N's neighbor is unvisited & distance is smaller, distance update & prevNode update
        for (auto it = nodes[min_index]->anodes.begin(); it != nodes[min_index]->anodes.end(); it++)
        {
            neighbor_index = (*it).first->index;
            if (nodes[neighbor_index] != nullptr && !nodeInfo[neighbor_index].visited && (*it).second < nodeInfo[neighbor_index].distance)
            {
                nodeInfo[neighbor_index].distance = (*it).second;
                nodeInfo[neighbor_index].prevNode = nodes[min_index];
            }
        }
    }

    // print nodeInfo
    Node *prevNode = nullptr;
    for (int i = 0; i < size; i++)
    {
        if (nodes[i] != nullptr)
        {
            prevNode = nodeInfo[i].prevNode;
            cout << "Node " << i;
            cout << " - visited: " << nodeInfo[i].visited << ", parent node: ";
            if (prevNode)
                cout << prevNode->index;
            else
                cout << "null";
            cout << ", distance from parent Node: " << nodeInfo[i].distance << endl;
            cout << "path from Node " << i << " to " << startIndex << ": " << i;
            while (prevNode != nullptr)
            {
                cout << " -> " << prevNode->index;
                prevNode = nodeInfo[prevNode->index].prevNode;
            }
            cout << endl;
        }
    }
    delete[] nodeInfo;
    return;
}

void WeightedGraph::Prim_pq(int startIndex)
{
    struct NodeInfo
    {
        /* data */
        int index;
        int distance = INF;
        bool visited = false;
        Node *prevNode = nullptr;
    };
    struct compare
    {
        bool operator()(NodeInfo n1, NodeInfo n2)
        {
            return n1.distance > n2.distance; // greater -> min heap
        }
    };
    int min_distance;
    int min_index;
    Node *min_prevNode;
    int neighbor_index;
    int size = nodes.size();
    NodeInfo *nodeInfo = new NodeInfo[size];

    priority_queue<NodeInfo, vector<NodeInfo>, compare> pq;

    if (startIndex >= 0 && startIndex < size && nodes[startIndex] != nullptr)
    {
        nodeInfo[startIndex].distance = 0;
    }

    for (int i = 0; i < size; i++)
    {
        nodeInfo[i].index = i;
        if (nodes[i] != nullptr)
            pq.push(nodeInfo[i]);
    }

    while (1)
    {
        // find unvisited, min distance node N.
        // if all unvisited node is infinity distance, stop loop.
        if (pq.empty())
            break;
        min_distance = pq.top().distance;
        min_index = pq.top().index;
        min_prevNode = pq.top().prevNode;
        pq.pop();
        if (min_distance == INF)
            break;
        // if N is not visited, update nodeInfo. else erase
        if (!nodeInfo[min_index].visited)
        {
            nodeInfo[min_index].distance = min_distance;
            nodeInfo[min_index].prevNode = min_prevNode;
            nodeInfo[min_index].visited = true;
        }
        else
            continue;

        // update N's neighbor
        // if N's neighbor is unvisited & distance is smaller, distance update & prevNode update
        for (auto it = nodes[min_index]->anodes.begin(); it != nodes[min_index]->anodes.end(); it++)
        {
            neighbor_index = (*it).first->index;
            if (nodes[neighbor_index] != nullptr && !nodeInfo[neighbor_index].visited && (*it).second < nodeInfo[neighbor_index].distance)
            {
                nodeInfo[neighbor_index].distance = (*it).second;
                nodeInfo[neighbor_index].prevNode = nodes[min_index];
                pq.push(nodeInfo[neighbor_index]);
            }
        }
    }

    // print nodeInfo
    Node *prevNode = nullptr;
    for (int i = 0; i < size; i++)
    {
        if (nodes[i] != nullptr)
        {
            cout << "Node " << i;
            cout << " - visited: " << nodeInfo[i].visited << ", distance from Node " << startIndex << ": " << nodeInfo[i].distance << endl;
            cout << "path from Node " << i << " to " << startIndex << ": " << i;
            prevNode = nodeInfo[i].prevNode;
            while (prevNode != nullptr)
            {
                cout << " -> " << prevNode->index;
                prevNode = nodeInfo[prevNode->index].prevNode;
            }
            cout << endl;
        }
    }
    delete[] nodeInfo;
    return;
}

void WeightedGraph::Kruskal()
{
    if (directed)
        return;

    struct Edge
    {
        Edge(int w, int _x, int _y) : weight(w), x(_x), y(_y){};
        int weight;
        int x; // small
        int y; // large
        bool operator<(Edge e2)
        {
            if (weight == e2.weight)
            {
                if (x == e2.x)
                {
                    return y < e2.y;
                }
                return x < e2.x;
            }
            return weight < e2.weight;
        }

        bool operator>(Edge e2)
        {
            if (weight == e2.weight)
            {
                if (x == e2.x)
                {
                    return y > e2.y;
                }
                return x > e2.x;
            }
            return weight > e2.weight;
        }

        bool operator==(Edge e2)
        {
            return (weight == e2.weight) && (x == e2.x) && (y == e2.y);
        }
    };

    vector<Edge> allEdges;
    vector<Edge> MSTEdges;

    // fill allEdges
    for (auto it = nodes.begin(); it != nodes.end(); it++)
    {
        int x = (*it)->index;
        int y;
        for (auto a_it = (*it)->anodes.begin(); a_it != (*it)->anodes.end(); a_it++)
        {
            y = (*a_it).first->index;
            if (x == y)
                continue;
            Edge e = {0, 0, 0};
            if (x > y)
            {
                e = {(*a_it).second, y, x};
            }
            else
            {
                e = {(*a_it).second, x, y};
            }
            auto eit = lower_bound(allEdges.begin(), allEdges.end(), e);
            if (eit == allEdges.end())
            {
                allEdges.push_back(e);
            }
            else if (!((*eit) == e))
            {
                allEdges.insert(eit, e);
            }
        }
    }

    // Kruskal: find MSTEdges
    UnionFind unionFind(nodes.size());
    auto it = allEdges.begin();
    int px, py;
    while (it != allEdges.end() && MSTEdges.size() != nodeCount - 1)
    {
        px = unionFind.Find((*it).x);
        py = unionFind.Find((*it).y);
        if (px != py)
        {
            MSTEdges.push_back(*it);
            unionFind.Union(px, py);
        }
        it++;
    }

    // print result
    for (auto it = MSTEdges.begin(); it != MSTEdges.end(); it++)
    {
        cout << "edge weight: " << (*it).weight << ", node 1: " << (*it).x << ", node 2: " << (*it).y << endl;
    }

    return;
}

bool WeightedGraph::BellmanFord(int startIndex)
{
    int V = nodes.size();
    int *distance = new int[V];
    int *parent = new int[V];
    for (int i = 0; i < V; i++)
    {
        distance[i] = INF;
        parent[i] = i;
    }

    if (0 <= startIndex && startIndex < V)
        distance[startIndex] = 0;

    // edge relaxation V-1 times
    int s, e, w;
    bool distChanged;
    for (int i = 1; i < V; i++)
    {
        distChanged = false;
        // edge relaxation
        for (auto it = edges.begin(); it != edges.end(); it++)
        {
            s = (*it).start;
            e = (*it).end;
            w = (*it).weight;
            if (distance[s] != INF && distance[s] + w < distance[e])
            {
                distance[e] = distance[s] + w;
                parent[e] = s;
                distChanged = true;
            }
        }
        if (!distChanged)
            break;
    }

    // negative cycle check
    bool negCycle = false;
    for (auto it = edges.begin(); it != edges.end(); it++)
    {
        s = (*it).start;
        e = (*it).end;
        w = (*it).weight;
        if (distance[s] != INF && distance[s] + w < distance[e])
        {
            negCycle = true;
        }
    }
    if (!negCycle)
    {
        // print result
        int prevNode;
        for (int i = 0; i < V; i++)
        {
            if (nodes[i] != nullptr)
            {
                prevNode = parent[i];
                cout << "Node " << i;
                cout << " - distance: " << distance[i] << endl;
                cout << "path from Node " << i << " to " << startIndex << ": " << i;
                while (prevNode != parent[prevNode])
                {
                    cout << " -> " << prevNode;
                    prevNode = parent[prevNode];
                }
                cout << " -> " << prevNode << endl;
            }
        }
    }
    else
    {
        cout << "negative cycle detected" << endl;
    }

    delete[] distance, parent;
    return negCycle;
}

bool WeightedGraph::FloydWarshall()
{
    int V = nodes.size();
    vector<vector<int>> distance;
    vector<vector<int>> parent;
    int s, e, w;
    // initial setting
    for (int i = 0; i < V; i++)
    {
        vector<int> row;
        vector<int> prow;
        for (int j = 0; j < V; j++)
        {
            row.push_back(INF);
            prow.push_back(-1);
        }
        distance.push_back(row);
        parent.push_back(prow);
    }

    for (int i = 0; i < V; i++)
    {
        distance[i][i] = 0;
    }

    for (auto it = edges.begin(); it != edges.end(); it++)
    {
        s = (*it).start;
        e = (*it).end;
        w = (*it).weight;
        distance[s][e] = w;
        parent[s][e] = e;
    }

    // 3 for
    for (int k = 0; k < V; k++)
        for (int i = 0; i < V; i++)
            for (int j = 0; j < V; j++)
                if ((distance[i][k] != INF) && (distance[k][j] != INF) && (distance[i][k] + distance[k][j] < distance[i][j]))
                {
                    distance[i][j] = distance[i][k] + distance[k][j];
                    parent[i][j] = parent[i][k];
                }

    // check cycle
    for (int i = 0; i < V; i++)
        if (distance[i][i] < 0)
            return false;

    // print
    int nextNode;
    for (int i = 0; i < 1; i++)
    {
        for (int j = 0; j < V; j++)
        {
            if (nodes[i] != nullptr && nodes[j] != nullptr)
            {
                cout << "From Node " << i << " to Node " << j;
                cout << " - distance: " << distance[i][j] << endl;
                cout << "path: " << i;
                nextNode = parent[i][j];
                while (nextNode != -1 && nextNode != j)
                {
                    cout << " -> " << nextNode;
                    nextNode = parent[nextNode][j];
                }
                cout << " -> " << j << endl;
            }
        }
    }

    return true;
}

int WeightedGraph::FordFulkerson(int source, int sink)
{
    // assume that all edges are positive
    int V = nodes.size();
    if (!directed || source < 0 || source >= V || sink < 0 || sink >= V)
        return 0;
    vector<vector<int>> res;
    for (int i = 0; i < V; i++)
    {
        vector<int> row(V, 0);
        res.push_back(row);
    }
    for (auto it = edges.begin(); it != edges.end(); it++)
    {
        res[(*it).start][(*it).end] += (*it).weight;
    }
    int *parent = new int[V];
    bool pathExist = true;
    int maxFlow = 0;
    int minCap;
    int p;
    while (pathExist)
    {
        pathExist = false;
        for (int i = 0; i < V; i++)
        {
            parent[i] = -1;
        }
        parent[source] = source;
        minCap = FF_DFS(source, sink, res, parent);
        if (minCap != INF)
        {
            pathExist = true;
            // increase maxFlow
            maxFlow += minCap;
            // path cancellation
            p = sink;
            while (p != parent[p])
            {
                res[parent[p]][p] -= minCap;
                res[p][parent[p]] += minCap;
                p = parent[p];
            }
        }
    }
    delete[] parent;
    return maxFlow;
}

int WeightedGraph::FF_DFS(int index, int sink, vector<vector<int>> &res, int *parent)
{
    if (index == sink)
        return res[parent[sink]][sink];

    int V = res.size();
    int minCap = INF;
    int temp;
    for (int ai = 0; ai < V; ai++)
    {
        if (res[index][ai] > 0 && parent[ai] == -1)
        {
            parent[ai] = index;
            temp = FF_DFS(ai, sink, res, parent);
            if (temp != INF) // if find a path
                minCap = res[index][ai] < temp ? res[index][ai] : temp;
        }
    }
    return minCap;
}
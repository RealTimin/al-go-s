#include <iostream>
#include <list>
#include <queue>
#include <stack>
#include <vector>

using namespace std;

class Node
{
public:
    Node(int _index) : index(_index) { anodes.clear(); }
    ~Node() { anodes.clear(); }
    int index;
    list<Node *> anodes;
};

class Edge
{
public:
    Edge(int s, int e) : start(s), end(e){};
    int start;
    int end;
};

class Graph
{
public:
    Graph() : nodeCount(0), edgeCount(0), directed(false) { nodes.clear(); }
    Graph(int _nc, bool _d = false) : nodeCount(_nc), edgeCount(0), directed(_d)
    {
        nodes.clear();
        for (int i = 0; i < nodeCount; i++)
        {
            Node *newNode = new Node(i);
            nodes.push_back(newNode);
        }
    }

    ~Graph()
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
    void InsertNode(int index);      // insert node of given index if the node is not already in the graph.
    void InsertEdge(int i1, int i2); // insert edge from i1 to i2 (if undirected, also add edge from i2 to i1)
    void BFS(int startIndex);
    void DFS(int startIndex);
    bool isConnected(int i1, int i2);
    bool hasCycle();
    void Kosaraju();
    void Tarjan();
    bool isBipartite();

private:
    vector<Node *> nodes;
    vector<Edge> edges;
    int nodeCount;
    int edgeCount;
    bool directed;
    void DFSTraversal(bool *visited, int index);
    bool hasCycleHelper_directed(int *visited, int *finished, int *parent, int index);
    bool hasCycleHelper_indirected(int *visited, int *finished, int *parent, int index);
    int Kosaraju_first_DFS(int index, int *visited, int *finishTime, int time);
    void Kosaraju_second_DFS(int index, int *visited, vector<int> &scc);
    int Tarjan_DFS(int index, int &curDisc, int &curSscID, int *discover, int *sscID, stack<int> &s);
    bool isBipartite_DFS(int index, int *color);
};

void Graph::InsertNode()
{
    int index;
    for (index = 0; index < nodes.size() && nodes[index] != nullptr; index++)
        ;

    InsertNode(index);
}
void Graph::InsertNode(int index)
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

void Graph::InsertEdge(int i1, int i2)
{
    InsertNode(i1);
    InsertNode(i2);
    if (i1 >= 0 && i2 >= 0)
    {
        if (directed)
        {
            nodes[i1]->anodes.push_back(nodes[i2]);
            edges.push_back(Edge(i1, i2));
            edgeCount++;
        }
        else
        {
            nodes[i2]->anodes.push_back(nodes[i1]);
            nodes[i1]->anodes.push_back(nodes[i2]);
            edges.push_back(Edge(i1, i2));
            edges.push_back(Edge(i2, i1));
            edgeCount++;
        }
    }
}

void Graph::BFS(int startIndex)
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
                d.push((*it));
            }
            visited[index] = true;
        }
        d.pop();
    }
    delete[] visited;
    return;
}

void Graph::DFS(int startIndex)
{
    bool *visited = new bool[nodes.size()];
    for (int i = 0; i < nodes.size(); i++)
        visited[i] = false;
    if (startIndex >= 0 && startIndex < nodes.size() && nodes[startIndex] != nullptr)
        DFSTraversal(visited, startIndex);
    delete[] visited;
    return;
}

void Graph::DFSTraversal(bool *visited, int index)
{
    visited[index] = true;
    cout << nodes[index]->index << ' ';
    int ni;
    for (auto it = nodes[index]->anodes.begin(); it != nodes[index]->anodes.end(); it++)
    {
        ni = (*it)->index;
        if (visited[ni] == false)
            DFSTraversal(visited, ni);
    }
    return;
}

bool Graph::hasCycle()
{
    int size = nodes.size();
    bool cycle = false;
    int *visited = new int[size];
    int *finished = new int[size];
    int *parent = new int[size];
    int si;
    for (int i = 0; i < size; i++)
    {
        visited[i] = false;
        finished[i] = false;
        parent[i] = i;
    }
    if (directed)
    {
        // DFS based cycle detection
        // using visited, finished, parent(parent is just for printing cycle)
        int *in_Degree = new int[size];
        bool allChecked = false;
        int zi;
        for (auto it = nodes.begin(); it != nodes.end(); it++)
        {
            for (auto a_it = (*it)->anodes.begin(); a_it != (*it)->anodes.end(); a_it++)
            {
                in_Degree[(*a_it)->index]++;
            }
        }

        // DFS based cycle detection
        while (!allChecked)
        {
            zi = -1;
            si = -1;
            for (int i = 0; i < size; i++)
            {
                if (!visited[i])
                {
                    si = i;
                    if (in_Degree[i] == 0)
                        zi = i;
                }
            }
            if (si == -1)
                break;
            if (zi == -1)
                cycle = true; // there is a cycle.
            else
                si = zi;
            if (hasCycleHelper_directed(visited, finished, parent, si)) // else, start DFS from si.
                cycle = true;
            allChecked = true;
            for (int i = 0; i < size; i++)
            {
                if (!visited[i])
                    allChecked = false;
            }
        }

        delete[] in_Degree;
    }
    else
    {
        // indirected graph -> only tree edge & back edge

        bool allChecked = false;
        // DFS based cycle detection
        while (!allChecked)
        {
            si = -1;
            for (int i = 0; i < size; i++)
                if (!visited[i])
                    si = i;
            if (si == -1)
                break;
            if (hasCycleHelper_indirected(visited, finished, parent, si))
                cycle = true;
            allChecked = true;
            for (int i = 0; i < size; i++)
                if (!visited[i])
                    allChecked = false;
        }
    }
    delete[] visited, finished, parent;
    return cycle;
}

bool Graph::hasCycleHelper_directed(int *visited, int *finished, int *parent, int index)
{
    visited[index] = true;
    int a_index;
    bool cycle = false;
    for (auto a_it = nodes[index]->anodes.begin(); a_it != nodes[index]->anodes.end(); a_it++)
    {
        a_index = (*a_it)->index;
        if (!visited[a_index])
        {
            // WHITE vertex
            parent[a_index] = index; // set parent index
            if (hasCycleHelper_directed(visited, finished, parent, a_index))
                cycle = true;
        }
        else if (!finished[a_index])
        {
            // GREY vertex
            cycle = true;
            // TODO: print cycle
            int cycleIndex = index;
            cout << "Node index in a cycle: ";
            while (cycleIndex != a_index)
            {
                cout << cycleIndex << ' ';
                cycleIndex = parent[cycleIndex];
            }
            cout << a_index << ' ' << index << endl;
        }
        else
        {
            // BLACK vertex
        }
    }
    finished[index] = true;
    return cycle;
}

bool Graph::hasCycleHelper_indirected(int *visited, int *finished, int *parent, int index)
{
    visited[index] = true;
    int a_index;
    bool cycle = false;
    for (auto a_it = nodes[index]->anodes.begin(); a_it != nodes[index]->anodes.end(); a_it++)
    {
        a_index = (*a_it)->index;
        if (!visited[a_index])
        {
            // WHITE vertex
            parent[a_index] = index; // set parent index
            if (hasCycleHelper_indirected(visited, finished, parent, a_index))
                cycle = true;
        }
        else if (!finished[a_index])
        {
            if (parent[index] != a_index) // if adjacent node is not my parent node
            {
                // GREY vertex
                cycle = true;
                // TODO: print cycle
                int cycleIndex = index;
                cout << "Node index in a cycle: ";
                while (cycleIndex != a_index)
                {
                    cout << cycleIndex << ' ';
                    cycleIndex = parent[cycleIndex];
                }
                cout << a_index << ' ' << index << endl;
            }
        }
        else
        {
            // BLACK vertex. Zero possibility in indirected graph.
        }
    }
    finished[index] = true;
    return cycle;
}

void Graph::Kosaraju()
{
    // TODO:
    int V = nodes.size();
    int *finishTime = new int[V];
    int *visited = new int[V];
    for (int i = 0; i < V; i++)
    {
        finishTime[i] = -1;
        visited[i] = 0;
    }

    bool DFSfinished = false;
    int time = 0;
    // first DFS. Mark finishTime.
    for (int i = 0; i < V; i++)
    {
        if (!visited[i])
        {
            time = Kosaraju_first_DFS(i, visited, finishTime, time);
        }
    }

    // second DFS, find SCCs
    Graph rev(V, true); // reverse graph
    for (auto it = edges.begin(); it != edges.end(); it++)
    {
        rev.InsertEdge((*it).end, (*it).start);
    }
    priority_queue<pair<int, int>> maxFinishTime; // {finishTime[i], i}
    for (int i = 0; i < V; i++)
    {
        visited[i] = 0;
        maxFinishTime.push({finishTime[i], i});
    }
    vector<vector<int>> SCCs;
    vector<int> scc;
    int index;
    for (int i = 0; i < V; i++)
    {
        index = maxFinishTime.top().second;
        if (maxFinishTime.top().first != -1 && !visited[index])
        {
            rev.Kosaraju_second_DFS(index, visited, scc);
            SCCs.push_back(scc);
            scc.clear();
        }
        maxFinishTime.pop();
    }

    // print
    for (auto it = SCCs.begin(); it != SCCs.end(); it++)
    {
        cout << "scc: ";
        for (auto iit = (*it).begin(); iit != (*it).end(); iit++)
        {
            cout << (*iit) << ' ';
        }
        cout << endl;
    }

    delete[] finishTime, visited;
    return;
}

int Graph::Kosaraju_first_DFS(int index, int *visited, int *finishTime, int time)
{
    // simple DFS, marking finishTime
    int V = nodes.size();
    visited[index] = true;
    if (nodes[index] == nullptr)
        return time;
    int ai;
    for (auto it = nodes[index]->anodes.begin(); it != nodes[index]->anodes.end(); it++)
    {
        ai = (*it)->index;
        if (nodes[ai] != nullptr && !visited[ai])
            time = Kosaraju_first_DFS(ai, visited, finishTime, time);
    }
    finishTime[index] = time++;
    return time;
}

void Graph::Kosaraju_second_DFS(int index, int *visited, vector<int> &scc)
{
    // executed in reversed graph, DFS to not visited nodes and mark their indexes at scc
    int V = nodes.size();
    visited[index] = true;
    if (nodes[index] == nullptr)
        return;
    scc.push_back(index);
    int ai;
    for (auto it = nodes[index]->anodes.begin(); it != nodes[index]->anodes.end(); it++)
    {
        ai = (*it)->index;
        if (nodes[ai] != nullptr && !visited[ai])
            Kosaraju_second_DFS(ai, visited, scc);
    }
    return;
}

void Graph::Tarjan()
{
    // TODO:
    int V = nodes.size();
    int *discover = new int[V];
    int *sscID = new int[V];
    stack<int> s;
    for (int i = 0; i < V; i++)
    {
        discover[i] = -1;
        sscID[i] = -1;
    }
    bool DFSfinished = false;
    int index;
    int curDisc = 0;
    int curSscID = 0;
    for (int i = 0; i < V; i++)
    {
        if (discover[i] == -1)
        {
            Tarjan_DFS(i, curDisc, curSscID, discover, sscID, s);
        }
    }
    delete[] discover, sscID;
    return;
}

// return: low[index]
int Graph::Tarjan_DFS(int index, int &curDisc, int &curSscID, int *discover, int *sscID, stack<int> &s)
{
    discover[index] = ++curDisc;
    int ret = curDisc;
    if (nodes[index] == nullptr)
        return ret;
    s.push(index);
    int ai;
    for (auto it = nodes[index]->anodes.begin(); it != nodes[index]->anodes.end(); it++)
    {
        ai = (*it)->index;
        if (discover[ai] == -1)
            ret = min(ret, Tarjan_DFS(ai, curDisc, curSscID, discover, sscID, s));
        else if (sscID[ai] == -1)
            ret = min(ret, discover[ai]);
    }

    // check ssc (if discover[index] == ret)
    int x;
    if (discover[index] == ret)
    {
        // print ssc
        cout << "ssc: ";
        while (!s.empty())
        {
            x = s.top();
            sscID[x] = curSscID;
            s.pop();
            cout << x << ' ';
            if (x == index)
                break;
        }
        cout << endl;
        curSscID++;
    }
    return ret;
}

bool Graph::isBipartite()
{
    if (directed)
    {
        cout << "cannot check because it is directed graph. " << endl;
        return false;
    }
    int V = nodes.size();
    int *color = new int[V]; // -1: unvisited, 0: color 0, 1: color 1
    bool bipartite = true;
    for (int i = 0; i < V; i++)
        color[i] = -1;
    for (int i = 0; i < V; i++)
    {
        if (color[i] == -1 && !isBipartite_DFS(i, color))
            bipartite = false;
    }
    delete[] color;
    return bipartite;
}

bool Graph::isBipartite_DFS(int index, int *color)
{
    int V = nodes.size();
    if (nodes[index] == nullptr || index < 0 || index >= V)
        return true; // maintain previous result

    if (color[index] == -1) // If it is the first DFS step, this will be executed.
        color[index] = 0;
    int otherColor = color[index] ? 0 : 1;
    int ai;
    bool bipartite = true;
    for (auto it = nodes[index]->anodes.begin(); it != nodes[index]->anodes.end(); it++)
    {
        ai = (*it)->index;
        if (color[ai] == color[index]) // not bipartite
            bipartite = false;
        else if (color[ai] == -1) // unvisited
        {
            color[ai] = otherColor;
            if (!isBipartite_DFS(ai, color))
                bipartite = false;
        }
        // else // color[ai] == otherColor -> do nothing
    }
    return bipartite;
}

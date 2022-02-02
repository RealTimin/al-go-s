#include <iostream>
#include <list>
#include <deque>

using namespace std;

template <class T>
class SimpleTree
{
private:
    T value;
    SimpleTree *parent;
    list<SimpleTree *> children;

public:
    SimpleTree(T const &obj = T(), SimpleTree *p = nullptr) : value(obj), parent(p) {}
    T get_value() const { return value; }
    SimpleTree<T> *get_parent() const { return parent; }
    int get_degree() const { return children.size(); };
    bool is_root() const { return parent == nullptr; }
    bool is_leaf() const { return children.empty(); }
    SimpleTree<T> *get_child(int n) const; // return n th child's address
    SimpleTree<T> *attach(T const &obj);   // make SimpleTree object & push it in children list
    // void attach_subtree(SimpleTree *);
    // void detach_from_parent();

    int size() const;
    int height() const;
    int depth() const;

    void BFS_print();
    void DFS_print(int step = 0) const;
};

template <class T>
SimpleTree<T> *SimpleTree<T>::get_child(int n) const
{
    if (n < 0 || n > get_degree())
        return nullptr;
    auto it = children.begin();

    for (int i = 1; i < n; i++)
    {
        it++;
    }
    return *it;
}

template <class T>
SimpleTree<T> *SimpleTree<T>::attach(T const &obj)
{
    SimpleTree<T> *child = new SimpleTree<T>(obj, this);
    children.push_back(child);
    return child;
}

template <class T>
int SimpleTree<T>::size() const
{
    int size = 1;
    for (auto it = children.begin(); it != children.end(); it++)
    {
        size += (*it)->size();
    }
    return size;
}

template <class T>
int SimpleTree<T>::height() const
{
    // cf) tree with one node: height 0
    int child_height_max = -1;
    int child_height;
    for (auto it = children.begin(); it != children.end(); it++)
    {
        child_height = (*it)->height();
        if (child_height > child_height_max)
            child_height_max = child_height;
    }
    return child_height_max + 1;
}

template <class T>
int SimpleTree<T>::depth() const
{
    int depth = 0;
    SimpleTree<T> *p = parent;
    while (p != nullptr)
    {
        depth++;
        p = p->parent;
    }
    return depth;
}

template <class T>
void SimpleTree<T>::BFS_print()
{
    deque<SimpleTree *> q;
    SimpleTree *tree;
    // q.push_back(static_cast<SimpleTree<T>>(this));
    q.push_back(this);
    while (!q.empty())
    {
        tree = q.front();
        cout << tree->value << ' ';
        auto end_it = tree->children.end();
        for (auto it = tree->children.begin(); it != end_it; it++)
        {
            q.push_back(*it);
        }
        q.pop_front();
    }
    cout << endl;
    return;
}

template <class T>
void SimpleTree<T>::DFS_print(int step) const
{
    // postorder traversal
    // step is for printing identation

    if (step > 0)
        for (int i = 0; i < step; i++)
            cout << "    ";
    cout << value << endl;
    for (auto it = children.begin(); it != children.end(); it++)
    {
        (*it)->DFS_print(step + 1);
    }
    return;
}

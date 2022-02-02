#include <iostream>

using namespace std;

template <typename Comparable>
class BinarySearchTree
{
public:
    BinarySearchTree() : root(nullptr) {}
    // BinarySearchTree(const BinarySearchTree &rhs); // copy constructor
    // BinarySearchTree(BinarySearchTree &&rhs);      // move constructor
    ~BinarySearchTree() { makeEmpty(root); }

    const Comparable &findMin() const { return findMin(root)->element; }
    const Comparable &findMax() const { return findmax(root)->element; }
    bool contains(const Comparable &x) const { return contains(x, root); }
    bool isEmpty() const { return root == nullptr; }
    void printTree(ostream &out = cout) const { printTree(root, out); }
    void printTree_preorder(ostream &out = cout) const { printTree_preorder(root, out, 0); }

    void makeEmpty() { makeEmpty(root); }
    void insert(const Comparable &x) { insert(x, root); }
    // void insert(Comparable &&x) { insert(x, root); }
    void remove(const Comparable &x) { remove(x, root); }

    // BinarySearchTree &operator=(const BinarySearchTree &rhs);
    // BinarySearchTree &operator=(BinarySearchTree &&rhs);

private:
    struct BinaryNode
    {
        Comparable element;
        BinaryNode *left;
        BinaryNode *right;

        BinaryNode(const Comparable &theElement, BinaryNode *lt, BinaryNode *rt)
            : element{theElement}, left{lt}, right{rt} {}

        BinaryNode(Comparable &&theElement, BinaryNode *lt, BinaryNode *rt)
            : element{std::move(theElement)}, left{lt}, right{rt} {}
    };

    BinaryNode *root;

    void insert(const Comparable &x, BinaryNode *&t);
    // void insert(Comparable &&x, BinaryNode *&t);
    void remove(const Comparable &x, BinaryNode *&t);
    BinaryNode *findMin(BinaryNode *t) const;
    BinaryNode *findMax(BinaryNode *t) const;
    bool contains(const Comparable &x, BinaryNode *t) const;
    void makeEmpty(BinaryNode *&t);
    void printTree(BinaryNode *t, ostream &out) const;
    void printTree_preorder(BinaryNode *t, ostream &out, int step) const;
    // BinaryNode *clone(BinaryNode *t) const;
};

template <typename Comparable>
void BinarySearchTree<Comparable>::insert(const Comparable &x, BinaryNode *&t)
{
    if (t == nullptr)
        t = new BinaryNode(x, nullptr, nullptr);
    else if (x == t->element)
        // no duplicate value
        return;
    else if (x < t->element)
        insert(x, t->left);
    else
        insert(x, t->right);
    return;
}

template <typename Comparable>
void BinarySearchTree<Comparable>::remove(const Comparable &x, BinaryNode *&t)
{
    if (t == nullptr)
        return;
    else if (x < t->element)
        remove(x, t->left);
    else if (x > t->element)
        remove(x, t->right);
    else
    {
        BinaryNode *temp;
        if (t->left == nullptr && t->right == nullptr)
        {
            delete t;
            t = nullptr;
        }
        else if (t->right == nullptr)
        {
            temp = t->left;
            delete t;
            t = temp;
        }
        else if (t->left == nullptr)
        {
            temp = t->right;
            delete t;
            t = temp;
        }
        else
        {
            temp = findMax(t->left);
            // temp = findMin(t->right);
            t->element = temp->element; // HACK: memory issue - what if t->element is not deleted?
            // remove(temp->element, findMax(t->left));
            remove(temp->element, t->left); // give temp as parameter makes no sense.
        }
    }
    return;
}

template <typename Comparable>
typename BinarySearchTree<Comparable>::BinaryNode *BinarySearchTree<Comparable>::findMin(BinaryNode *t) const
{
    if (t == nullptr)
        return nullptr;
    BinaryNode *minNode = t;
    while (minNode->left != nullptr)
    {
        minNode = minNode->left;
    }
    return minNode;
}

template <typename Comparable>
typename BinarySearchTree<Comparable>::BinaryNode *BinarySearchTree<Comparable>::findMax(BinaryNode *t) const
{
    if (t == nullptr)
        return nullptr;
    BinaryNode *maxNode = t;
    while (maxNode->right != nullptr)
    {
        maxNode = maxNode->right;
    }
    return maxNode;
}

template <typename Comparable>
bool BinarySearchTree<Comparable>::contains(const Comparable &x, BinaryNode *t) const
{
    if (t == nullptr)
        return false;
    else if (x == t->element)
        return true;
    else if (x < t->element)
        return contains(x, t->left);
    else
        return contains(x, t->right);
}

template <typename Comparable>
void BinarySearchTree<Comparable>::makeEmpty(BinaryNode *&t)
{
    if (t == nullptr)
        return;

    makeEmpty(t->left);
    makeEmpty(t->right);
    delete t;
    t = nullptr;
    return;
}

template <typename Comparable>
void BinarySearchTree<Comparable>::printTree(BinaryNode *t, ostream &out) const
{
    // inorder print
    if (t == nullptr)
        return;
    printTree(t->left, out);
    out << t->element << ' ';
    printTree(t->right, out);
    return;
}

template <typename Comparable>
void BinarySearchTree<Comparable>::printTree_preorder(BinaryNode *t, ostream &out, int step) const
{
    // preorder print
    if (t == nullptr)
        return;
    if (step > 0)
        for (int i = 0; i < step; i++)
            out << "    ";
    out << t->element << endl;
    printTree_preorder(t->left, out, step + 1);
    printTree_preorder(t->right, out, step + 1);
    return;
}

// template <typename Comparable>
// typename BinarySearchTree<Comparable>::BinaryNode *BinarySearchTree<Comparable>::clone(BinaryNode *t) const
// {
// }
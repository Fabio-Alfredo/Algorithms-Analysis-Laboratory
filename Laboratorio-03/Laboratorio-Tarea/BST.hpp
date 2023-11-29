#ifndef BST_HPP
#define BST_HPP

#include <string>
#include <vector>

using namespace std;

struct Node
{
    Node(string val);

    string data;
    Node *left;
    Node *right;
};

class BinarySearchTree
{
private:
    // Pointer to the root of the binary search tree
    Node *root;

    // Private helper functions for inserting and auto-completing
    void insert(Node *&node, const string &data);
    void inorder(Node *node, vector<string> &result);
    void search(Node *node, const string &prefix, vector<string> &suggestions);

public:
    // Constructor to create an empty binary search tree
    BinarySearchTree();

    // Public member functions
    void insert(const string &data);
    vector<string> search(const string &prefix);
    void inorder(vector<string> &result);
};

// Constructor to initialize a Binary Search Tree
// Initializes the 'root' pointer to nullptr, creating an empty tree.
BinarySearchTree::BinarySearchTree()
{
    root = nullptr;
}

// Constructor to initialize a Node with a given value
Node::Node(string val)
{
    data = val;
    left = nullptr;
    right = nullptr;
}

// Create a new Node and return a pointer to it
Node *createNode(string val)
{
    return new Node(val);
}

/*Insert a new Node with the given
'data' into the binary search tree*/
void BinarySearchTree::insert(const string &data)
{
    insert(root, data);
}

/*Insert a new Node with the given 'data' into
the binary search tree rooted at 'node'*/
void BinarySearchTree::insert(Node *&node, const string &data)
{
    if (node == nullptr)
    {
        node = new Node(data);
        return;
    }

    if (data < node->data)
    {
        insert(node->left, data);
    }
    else
    {
        insert(node->right, data);
    }
}

/*Perform an inorder traversal of the binary
search tree rooted at 'node' and store the results in 'result'
*/
void BinarySearchTree::inorder(Node *node, vector<string> &result)
{
    if (node == nullptr)
    {
        return;
    }

    inorder(node->left, result); // Visit left subtree
    result.push_back(node->data);
    inorder(node->right, result);
}

// Public function to perform an inorder traversal of the tree
void BinarySearchTree::inorder(vector<string> &result)
{
    inorder(root, result);
}

/*Search the binary search tree rooted at 'node' for
values matching the given 'prefix' and store them in 'suggestions'*/
void BinarySearchTree::search(Node *node, const string &prefix, vector<string> &suggestions)
{
    if (node == nullptr)
    {
        return;
    }

    if (node->data.find(prefix) == 0)
    {
        suggestions.push_back(node->data);
    }

    if (prefix < node->data)
    {
        search(node->left, prefix, suggestions);
    }
    search(node->right, prefix, suggestions);
}

/*Search the binary search tree for values that
match the given 'prefix' and return them
as a vector of suggestions*/
vector<string> BinarySearchTree::search(const string &prefix)
{
    vector<string> suggestions;
    search(root, prefix, suggestions);
    return suggestions;
}



#endif
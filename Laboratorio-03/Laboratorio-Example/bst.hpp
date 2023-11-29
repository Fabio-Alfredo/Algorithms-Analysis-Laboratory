#include "object.hpp"

#ifndef BST_HPP
#define BST_HPP

#include <iostream>

using namespace std;

// Define a struct to represent a Node in a binary search tree
struct Node
{
    Battalion data;
    Node *left;
    Node *right;
    Node *parent;
};

// Enumeration for different positions of a node in the tree
enum position
{
    ROOT,
    LEFT,
    RIGHT
};

// BinarySearchTree class definition
class BinarySearchTree
{
private:
    Node *root;
    int _size;
    void Inorden(Node *node);
    void Preorden(Node *node);
    void Postorden(Node *node);
    void Transplant(Node *u, Node *v);

    Node *NewNode(Battalion data);

public:
    // Constructor to initialize an empty binary search tree
    BinarySearchTree();

    // Constructor to initialize a binary search tree with an array of Battalion data
    BinarySearchTree(Battalion *data, int size);

    int size();

    Node *Minimum(Node *node);
    Node *Maximum(Node *node);

    Node *Successor(Battalion data);
    Node *Predecessor(Battalion data);
    Node *TreeSearch(Battalion data, Node *pointer);
    Node *IterativeTreeSearch(Battalion data, Node *pointer);
    void Display(int order);
    Node *getRoot();

    void Insert(Battalion data);
    void Delete(Battalion budget);
};

// Constructor to initialize an empty binary search tree
BinarySearchTree::BinarySearchTree()
{
    root = NULL;
}

Node *BinarySearchTree::getRoot()
{
    return root;
}

// Constructor to initialize a binary search tree with an array of Battalion data
BinarySearchTree::BinarySearchTree(Battalion *data, int size)
{
    root = NULL;
    _size = size;
    for (int i = 0; i < _size; ++i)
    {
        Insert(data[i]);
    }
}

// Public member function to get the size of the tree
int BinarySearchTree::size()
{
    return _size;
}

// Private member function to perform an in-order traversal of the tree
void BinarySearchTree::Inorden(Node *node)
{
    if (node == NULL)
    {
        return;
    }

    // Recursively traverse the left subtree
    Inorden(node->left);
    cout << node->data.getCode() << "\t$" << node->data.getId() << "\t$" << node->data.getManpower() << "\t$" << node->data.getArmoredEquipment() << "\t$" << node->data.getBudget() << "\n";
    // Recursively traverse the right subtree
    Inorden(node->right);
}

// Preorder traversal function
void BinarySearchTree::Preorden(Node *node)
{
    if (node == NULL)
    {
        return;
    }

    cout << node->data.getCode() << "\t$" << node->data.getId() << "\t$" << node->data.getManpower() << "\t$" << node->data.getArmoredEquipment() << "\t$" << node->data.getBudget() << "\n";
    // Recursively traverse the left subtree in preorder
    Preorden(node->left);
    // Recursively traverse the right subtree in preorder
    Preorden(node->right);
}

// Postorder traversal function
void BinarySearchTree::Postorden(Node *node)
{
    if (node == NULL)
    {
        return;
    }

    // Recursively traverse the left subtree in postorder
    Inorden(node->left);
    // Recursively traverse the right subtree in postorder
    Inorden(node->right);
    cout << node->data.getCode() << "\t$" << node->data.getId() << "\t$" << node->data.getManpower() << "\t$" << node->data.getArmoredEquipment() << "\t$" << node->data.getBudget() << "\n";
}

// Create a new node with given Battalion data
Node *BinarySearchTree::NewNode(Battalion data)
{
    Node *newNode = new Node;
    newNode->data = data;
    newNode->left = nullptr;
    newNode->right = nullptr;

    return newNode;
}

// Check the position of a node in relation to its parent
position check_position(Node *node)
{
    if (node->parent == NULL)
    {
        return ROOT;
    }
    else if (node->parent->left == node)
    {
        return LEFT;
    }
    else
    {
        return RIGHT;
    }
}

// Transplant node u with node v in the tree
void BinarySearchTree::Transplant(Node *u, Node *v)
{
    switch (check_position(u))
    {
    case ROOT:
        root = v; // If u is the root, update the root with v
        break;
    case LEFT:
        u->parent->left = v; // If u is a left child, update u's parent's left child with v
        break;
    case RIGHT:
        u->parent->right = v; // If u is a right child, update u's parent's right child with v
        break;
    }

    if (v != nullptr || v != NULL)
    {
        v->parent = u->parent; // Update v's parent to be u's parent
    }
}

// Find and return the node with the minimum value in the tree, starting from the given node
Node *BinarySearchTree::Minimum(Node *node)
{
    if (node == NULL)
    {
        node = root; // If no node is given, start from the root
    }

    // Traverse the left child nodes until the minimum node is found
    while (node->left != NULL)
    {
        node = node->left;
    }
    return node;
}

// Find and return the node with the maximum value in the tree, starting from the given node
Node *BinarySearchTree::Maximum(Node *node)
{
    if (node == NULL)
    {
        node = root; // If no node is given, start from the root
    }

    // Traverse the right child nodes until the maximum node is found
    while (node->right != NULL)
    {
        node = node->right;
    }
    return node;
}

// Find and return the predecessor node of a node with the given Battalion data
Node *BinarySearchTree::Predecessor(Battalion data)
{
    Node *node = TreeSearch(data, root); // Search for the node with the given data

    // If the node is not found, return NULL
    if (node == NULL)
    {
        return NULL;
    }

    // If the node has a left subtree, find the maximum node in that subtree
    if (node->left != NULL)
    {
        return Maximum(node->left);
    }
    else
    {

        // If the node does not have a left subtree, traverse up the tree to find the predecessor
        Node *pre = node->parent;
        while (pre != NULL && node == pre->left)
        {
            node = pre;
            pre = pre->parent;
        }
        return pre;
    }
}

// Find and return the successor node of a node with the given Battalion data
Node *BinarySearchTree::Successor(Battalion data)
{

    Node *node = TreeSearch(data, root); // Search for the node with the given data

    // If the node is not found, return NULL
    if (node == NULL)
    {
        return NULL;
    }

    // If the node has a right subtree, find the minimum node in that subtree
    if (node->right != NULL)
    {
        return Minimum(node->right);
    }
    else
    {

        // If the node does not have a right subtree, traverse up the tree to find the successor
        Node *suc = node->parent;
        while (suc != NULL && node == suc->right)
        {
            node = suc;
            suc = suc->parent;
        }
        return suc;
    }
}

// Function to validate if a node's data matches a given Battalion data
bool validation(Node *node, Battalion data)
{
    if (node == NULL)
    {
        return false; // Node is NULL, data cannot match
    }

    // Compare all attributes of the Battalion data
    if (node->data.getCode() == data.getCode() && node->data.getId() == data.getId() && node->data.getManpower() == data.getManpower() && node->data.getArmoredEquipment() == data.getArmoredEquipment() && node->data.getBudget() == data.getBudget())
    {
        return true; // Data in the node matches the given data
    }
    return false; // Data does not match
}

// Recursive tree search function
Node *BinarySearchTree::TreeSearch(Battalion data, Node *pointer)
{
    if (pointer == NULL || validation(pointer, data))
    {
        return pointer; // Node is NULL or data matches, return the node
    }
    else if (data.getBudget() > pointer->data.getBudget())
    {
        return TreeSearch(data, pointer->right); // Search in the right subtree
    }
    else
    {
        return TreeSearch(data, pointer->left); // Search in the left subtree
    }
}

// Iterative tree search function
Node *BinarySearchTree::IterativeTreeSearch(Battalion data, Node *pointer)
{
    while (pointer != NULL)
    {
        if (validation(pointer, data))
        {
            return pointer; // Data matches, return the node
        }
        else if (pointer->data.getBudget() > data.getBudget())
        {
            pointer = pointer->left; // Move to the left subtree
        }
        else
        {
            pointer = pointer->right; // Move to the right subtree
        }
    }

    return NULL; // Data not found in the tree
}

// Display the tree in a specific order (in-order, pre-order, or post-order)
void BinarySearchTree::Display(int order)
{
    switch (order)
    {
    case 1:
        cout << "Inorden tree: \n";
        cout << "code \t id   manpower  equipment  budget \n";
        Inorden(root); // Display in-order
        break;
    case 2:
        cout << "Preorden tree: \n";
        Preorden(root); // Display preorder
        break;
    case 3:
        cout << "Inorden tree: \n";
        Postorden(root); // Display postorder
        break;
    default:
        // Invalid display option
        cout << "invalid option" << order << endl;
        break;
    }
}

// Insert a new node with the given Battalion data into the binary search tree
void BinarySearchTree::Insert(Battalion data)
{
    Node *newNode = NewNode(data); // Create a new node with the given data
    Node *aux = NULL;
    Node *root_aux = root;

    // Traverse the tree to find the appropriate position to insert the new node
    while (root_aux != NULL)
    {
        aux = root_aux;
        if (data.getBudget() < root_aux->data.getBudget())
        {
            root_aux = root_aux->left; // Move to the left subtree
        }
        else
        {
            root_aux = root_aux->right; // Move to the right subtree
        }
    }

    // Set the parent of the new node
    newNode->parent = aux;

    if (aux == NULL)
    {
        root = newNode; // If the tree was empty, set the new node as the root
    }
    else if (data.getBudget() < aux->data.getBudget())
    {
        aux->left = newNode; // Set as left child
    }
    else
    {
        aux->right = newNode; // Set as right child
    }
}

// Delete a node with the given Battalion data from the binary search tree
void BinarySearchTree::Delete(Battalion data)
{
    Node *root_aux = root;
    Node *data_aux = TreeSearch(data, root);
    if (data_aux == NULL)
    {
        return; // Data not found in the tree, no deletion required
    }

    // Handle deletion based on different cases
    if (data_aux->left == NULL)
    {
        Transplant(data_aux, data_aux->right); // If there's no left child, replace with right child
    }
    else if (data_aux->right == NULL)
    {
        Transplant(data_aux, data_aux->left); // If there's no right child, replace with left child
    }
    else
    {
        // Find the minimum node in the right subtree
        Node *minimum = Minimum(data_aux->right);
        if (minimum != data_aux->right)
        {
            // Transplant minimum node if it's not the right child
            Transplant(minimum, minimum->right);
            minimum->right = data_aux->right;
            minimum->right->parent = minimum->right;
        }

        // Replace the node with its successor (minimum)
        Transplant(data_aux, minimum);
        minimum->left = data_aux->left;
        minimum->left->parent = minimum;
    }
}

#endif
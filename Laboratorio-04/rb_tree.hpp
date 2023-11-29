#ifndef RB_TREE_HPP
#define RB_TREE_HPP

#include <iostream>
#include "pcb.hpp"

enum COLOR
{
    RED,
    BLACK
};

// Color Node Structure for Red-Black Tree
struct Node
{
    COLOR color;
    PCB data;
    Node *left, *right, *parent;
};

// Class for Red-Black Tree

class Red_Black_Tree
{
private:
    Node *root;
    int _size;
    Node *NIL;

    // Create Node
    void InitNIL();
    Node *createNode(PCB);

    // Rotations
    void LeftRotation(Node *);
    void RightRotation(Node *);

    // Fix Insert
    void FixInsert(Node *);
    void FixInsertRefactor(Node *);

    // Fix Delete
    void FixDelete(Node *);
    void FixDeleteRefactor(Node *);

    // Transplant
    void Transplant(Node *, Node *);

    // Order
    void Inorder(Node *);
    void Postorder(Node *);
    void Preorder(Node *);

public:
    // Constructor
    Red_Black_Tree();
    Red_Black_Tree(PCB *, int);

    // Search
    Node *Search(PCB, Node *);

    // Minimum
    Node *Minimum(Node *);

    // Insertion
    void Insert(PCB);

    // Delete
    void Delete(PCB);

    // Display
    void Display(int);

    // Display Tree Shape
    void DisplayTreeShape();

    // Destructor
    //~Red_Black_Tree();

    Node *getRoot();
    bool isEmpty();
};

// Destructor
/*Red_Black_Tree::~Red_Black_Tree()
{
    while (root != NULL)
    {
        Delete(root->data);
    }

    if (NIL != nullptr)
    {
        delete NIL;
    }
}*/

bool Red_Black_Tree::isEmpty()
{
    if (this->root == NIL)
    {
        std::cout << "\nTree emty\n";
        return true;
    }

    return false;
}

Node *Red_Black_Tree::getRoot()
{
    return root;
}

void Red_Black_Tree::InitNIL()
{
    PCB nullPCB;
    nullPCB.SetProcessID(0);
    nullPCB.SetVirtualRuntime(0);
    nullPCB.SetTimeToComplete(0);
    NIL = new Node;
    NIL->data = nullPCB;
    NIL->color = BLACK;
    NIL->left = NIL->right = NIL->parent = nullptr;
}

// Constructor
Red_Black_Tree::Red_Black_Tree()
{
    InitNIL();
    this->root = NIL;
    this->_size = 0;
}

Red_Black_Tree::Red_Black_Tree(PCB *arr, int size)
{
    InitNIL();
    this->root = NIL;
    this->_size = 0;
    for (int i = 0; i < size; i++)
        Insert(arr[i]);
}

Node *Red_Black_Tree::createNode(PCB data)
{
    Node *newNode = new Node();
    newNode->data = data;
    newNode->color = RED;
    newNode->left = newNode->right = newNode->parent = NIL;
    return newNode;
}

void Red_Black_Tree::LeftRotation(Node *data)
{
    Node *temp = data->right;
    data->right = temp->left;
    if (temp->left != NIL)
        temp->left->parent = data;
    temp->parent = data->parent;
    if (data->parent == NIL)
        this->root = temp;
    else if (data == data->parent->left)
        data->parent->left = temp;
    else
        data->parent->right = temp;
    temp->left = data;
    data->parent = temp;
}

void Red_Black_Tree::RightRotation(Node *data)
{
    Node *temp = data->left;
    data->left = temp->right;
    if (temp->right != NIL)
        temp->right->parent = data;
    temp->parent = data->parent;
    if (data->parent == NIL)
        this->root = temp;
    else if (data == data->parent->left)
        data->parent->left = temp;
    else
        data->parent->right = temp;
    temp->right = data;
    data->parent = temp;
}

// Fixes

void Red_Black_Tree::FixInsert(Node *node)
{
    Node *uncle = NULL;

    // Continue fixing the tree while the parent of the current node is red
    while (node->parent->color == RED)
    {
        // If the parent of the current node is the left child of its parent
        if (node->parent == node->parent->parent->left)
        {
            uncle = node->parent->parent->right;

            // Case 1: If the uncle of the current node is also red
            if (uncle->color == RED)
            {
                node->parent->color = BLACK;
                uncle->color = BLACK;
                node->parent->parent->color = RED;
                node = node->parent->parent; // Move up the tree to check for further violations
            }
            else
            {
                // Case 2: If the current node is the right child of its parent
                if (node == node->parent->right)
                {
                    node = node->parent;
                    LeftRotation(node);
                }
                // Case 3: If the current node is the left child of its parent
                node->parent->color = BLACK;
                node->parent->parent->color = RED;
                RightRotation(node->parent->parent);
            }
        }
        // If the parent of the current node is the right child of its parent (symmetric to the left case)
        else
        {
            uncle = node->parent->parent->left;

            // Case 1
            if (uncle->color == RED)
            {
                node->parent->color = BLACK;
                uncle->color = BLACK;
                node->parent->parent->color = RED;
                node = node->parent->parent; // Move up the tree
            }
            else
            {
                // Case 2
                if (node == node->parent->left)
                {
                    node = node->parent;
                    RightRotation(node);
                }
                // Case 3
                node->parent->color = BLACK;
                node->parent->parent->color = RED;
                LeftRotation(node->parent->parent);
            }

            // Check if we have reached the root to terminate the loop
            if (node == root)
                break;
        }
    }

    // Ensure the root of the tree is black to maintain the red-black tree properties
    root->color = BLACK;
}

void Red_Black_Tree::FixDelete(Node *node)
{
    Node *sibling = NULL;

    // Continue fixing the tree until the current node is not the root and is black
    while (node != root && node->color == BLACK)
    {
        // If the deleted node is the left child of its parent
        if (node == node->parent->left)
        {
            sibling = node->parent->right;

            // Case 1: If the sibling is red, perform rotations to balance the tree
            if (sibling->color == RED)
            {
                sibling->color = BLACK;
                node->parent->color = RED;
                LeftRotation(node->parent);
                sibling = node->parent->right;
            }

            // Case 2: If both sibling's children are black, make the sibling red
            if (sibling->left->color == BLACK && sibling->right->color == BLACK)
            {
                sibling->color = RED;
                node = node->parent;
            }
            // Case 3: If the sibling's right child is black, perform rotations and color changes
            else
            {
                if (sibling->right->color == BLACK)
                {
                    sibling->left->color = BLACK;
                    sibling->color = RED;
                    RightRotation(sibling);
                    sibling = node->parent->right;
                }

                sibling->color = node->parent->color;
                node->parent->color = BLACK;
                sibling->right->color = BLACK;
                LeftRotation(node->parent);
                node = root; // This case effectively ends the loop
            }
        }
        // If the deleted node is the right child of its parent (symmetric to the left case)
        else
        {
            sibling = node->parent->left;

            // Case 1
            if (sibling->color == RED)
            {
                sibling->color = BLACK;
                node->parent->color = RED;
                RightRotation(node->parent);
                sibling = node->parent->left;
            }

            // Case 2
            if (sibling->right->color == BLACK && sibling->left->color == BLACK)
            {
                sibling->color = RED;
                node = node->parent;
            }
            // Case 3
            else
            {
                if (sibling->left->color == BLACK)
                {
                    sibling->right->color = BLACK;
                    sibling->color = RED;
                    LeftRotation(sibling);
                    sibling = node->parent->left;
                }

                sibling->color = node->parent->color;
                node->parent->color = BLACK;
                sibling->left->color = BLACK;
                RightRotation(node->parent);
                node = root; // End the loop
            }
        }
    }

    // Set the color of the current node to black, ensuring the red-black tree properties are maintained
    node->color = BLACK;
}

// Transplant
void Red_Black_Tree::Transplant(Node *u, Node *v)
{
    if (u->parent == NIL)
        this->root = v;
    else if (u == u->parent->left)
        u->parent->left = v;
    else
        u->parent->right = v;
    v->parent = u->parent;
}

// Inorder
void Red_Black_Tree::Inorder(Node *data)
{
    if (data != NIL)
    {
        Inorder(data->left);
        data->data.DisplayPCB();
        Inorder(data->right);
    }
}

// Postorder
void Red_Black_Tree::Postorder(Node *data)
{
    if (data != NIL)
    {
        Postorder(data->left);
        Postorder(data->right);
        data->data.DisplayPCB();
    }
}

// Preorder
void Red_Black_Tree::Preorder(Node *data)
{
    if (data != NIL)
    {
        data->data.DisplayPCB();
        Preorder(data->left);
        Preorder(data->right);
    }
}

// Search
Node *Red_Black_Tree::Search(PCB data, Node *node = nullptr)
{
    if (this->root == NIL)
    {
        std::cout << "Tree is Empty" << std::endl;
        return nullptr;
    }
    if (node == nullptr)
        node = this->root;
    if (node == NIL || node->data.GetVirtualRuntime() == data.GetVirtualRuntime())
        return node;
    if (data.GetVirtualRuntime() < node->data.GetVirtualRuntime())
        return Search(data, node->left);
    else
        return Search(data, node->right);
}

// Minimum
Node *Red_Black_Tree::Minimum(Node *node)
{
    while (node->left != NIL)
        node = node->left;
    return node;
}

// Insert
void Red_Black_Tree::Insert(PCB data)
{
    try
    {
        Node *newNode = createNode(data);
        Node *it = this->root;
        Node *last_visited = NIL;
        while (it != NIL)
        {
            last_visited = it;
            if (newNode->data.GetVirtualRuntime() < it->data.GetVirtualRuntime())
                it = it->left;
            else
                it = it->right;
        }
        newNode->parent = last_visited;
        if (last_visited == NIL)
            this->root = newNode;
        else if (newNode->data.GetVirtualRuntime() < last_visited->data.GetVirtualRuntime())
            last_visited->left = newNode;
        else
            last_visited->right = newNode;
        this->FixInsert(newNode);
        this->_size++;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}

void Red_Black_Tree::Delete(PCB data)
{
    if (this->root == NIL)
    {
        std::cout << "Tree is Empty" << std::endl;
        return;
    }
    Node *toDelete = Search(data);
    if (toDelete == nullptr || toDelete == NIL)
    {
        std::cout << "Element not found" << std::endl;
        return;
    }
    Node *y = toDelete;
    Node *x;
    COLOR y_original_color = y->color;
    if (toDelete->left == NIL)
    {
        x = toDelete->right;
        this->Transplant(toDelete, toDelete->right);
    }
    else if (toDelete->right == NIL)
    {
        x = toDelete->left;
        this->Transplant(toDelete, toDelete->left);
    }
    else
    {
        y = this->Minimum(toDelete->right);
        y_original_color = y->color;
        x = y->right;
        if (y->parent != toDelete)
        {
            this->Transplant(y, y->right);
            y->right = toDelete->right;
            y->right->parent = y;
        }
        else
            x->parent = y;
        this->Transplant(toDelete, y);
        y->left = toDelete->left;
        y->left->parent = y;
        y->color = toDelete->color;
    }
    if (y_original_color == BLACK)
        this->FixDelete(x);
    delete toDelete;
}

// Display
void Red_Black_Tree::Display(int order = 1)
{

    if (this->root == NULL)
    {
        std::cout << "The tree is empty" << std::endl;
        return;
    }
    else
    {
        switch (order)
        {
        case 1:
            Inorder(this->root);
            std::cout << std::endl;
            break;
        case 2:
            Preorder(this->root);
            std::cout << std::endl;
            break;
        case 3:
            Postorder(this->root);
            std::cout << std::endl;
            break;
        default:
            std::cout << "The provided order is not valid" << std::endl;
            break;
        }
        std::cout << std::endl;
    }
}

// Display Tree Shape
void Red_Black_Tree::DisplayTreeShape()
{
    if (this->root == NIL)
    {
        std::cout << "Tree is Empty" << std::endl;
        return;
    }
    std::cout << "Root: " << this->root->data.GetProcessID() << std::endl;
    std::cout << "NIL: " << NIL->data.GetProcessID() << std::endl;
    std::cout << "Size: " << this->_size << std::endl;
    std::cout << "Inorder: ";
    Inorder(this->root);
    std::cout << std::endl;
    std::cout << "Preorder: ";
    Preorder(this->root);
    std::cout << std::endl;
    std::cout << "Postorder: ";
    Postorder(this->root);
    std::cout << std::endl;
}

#endif
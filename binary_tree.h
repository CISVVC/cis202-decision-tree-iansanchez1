//SOLUTION
#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <string>

using namespace std;

class Node
{
private:
    string data;
    Node* left;
    Node* right;
    friend class Binary_tree;
};

/*
   A binary tree in which each node has two children.
*/
class Binary_tree
{
public:
    /**
       Constructs an empty tree.
    */
    Binary_tree();

    /**
       Constructs a tree with one node and no children.
       @param root_data the data for the root
    */
    Binary_tree(string root_data);

    /**
       Constructs a binary tree.
       @param root_data the data for the root
       @param left the left subtree
       @param right the right subtree
    */
    Binary_tree(string root_data, Binary_tree left, Binary_tree right);


    /**
       Returns the height of this tree.
       @return the height
    */
    int height() const;

    /**
       Checks whether this tree is empty.
       @return true if this tree is empty
    */
    bool empty() const;

    /**
       Gets the data at the root of this tree.
       @return the root data
    */
    string data() const;

    /**
       Gets the left subtree of this tree.
       @return the left child of the root
    */
    Binary_tree left() const;

    /**
       Gets the right subtree of this tree.
       @return the right child of the root
    */
    Binary_tree right() const;

private:
    /**
       Returns the height of the subtree whose root is the given node.
       @param n a node or nullptr
       @return the height of the subtree, or 0 if n is nullptr
    */
    int height(const Node* n) const;

    Node* root;
};

#endif




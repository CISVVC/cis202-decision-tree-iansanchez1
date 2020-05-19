/*
 * File: binary_tree.cpp
 * Description: This program implements the Binary_tree class.
 * Author: Ian Sanchez Munoz
 * Email: ians2913@student.vvc.edu
 */
#include <algorithm>
#include "binary_tree.h"

using namespace std;

Binary_tree::Binary_tree()
{
    root = nullptr;
}

Binary_tree::Binary_tree(string root_data)
{
    root = new Node;
    root->data = root_data;
    root->left = nullptr;
    root->right = nullptr;
}

Binary_tree::Binary_tree(string root_data, Binary_tree left, Binary_tree right)
{
    root = new Node;
    root->data = root_data;
    root->left = left.root;
    root->right = right.root;
}

void Binary_tree::set(string steps, string root_data, Binary_tree left, Binary_tree right)
{
    set(root, steps, root_data, left, right);
}

void Binary_tree::set(Node* n, string steps, string root_data, Binary_tree left, Binary_tree right)
{
    if (steps.length() == 0)
    {
	n->data = root_data;
	n->left = left.root;
	n->right = right.root;
    }
    else
    {
	char direction = steps[0];
	steps.erase(0, 1);
	set(direction == '1' ? n-> left : n->right, steps, root_data, left, right);
    }
}

int Binary_tree::height(const Node* n) const
{
    if (n == nullptr)
    {
        return 0;
    }
    else
    {
        return 1 + max(height(n->left), height(n->right));
    }
}

int Binary_tree::height() const
{
    return height(root);
}

bool Binary_tree::empty() const
{
    return root == nullptr;
}

string Binary_tree::data() const
{
    return root->data;
}

Binary_tree Binary_tree::left() const
{
    Binary_tree result;
    result.root = root->left;
    return result;
}

Binary_tree Binary_tree::right() const
{
    Binary_tree result;
    result.root = root->right;
    return result;
}




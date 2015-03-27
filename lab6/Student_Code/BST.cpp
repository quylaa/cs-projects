// Written by Aleks Christensen

#include "BST.h"

BST::BST(){}

BST::~BST(){ BST::clear(); }

bool BST::addr(Node*& top, int data)
{
    if (top == NULL) { // there is no node here, add one
        top = new Node(data, NULL, NULL);
        return true;
    }
    else {
        if (data < top->data) {
            return addr(top->left, data); // recursively add to left subtree
        }
        else if (data > top->data) {
            return addr(top->right, data); // recursively add to right subtree
        }
        else return false;
    }
    return false;
}

bool BST::remover(Node*& top, int data)
{
    if (top == NULL) return false;

    if (data < top->data) {
        return remover(top->left, data);
    } else if (data > top->data) {
        return remover(top->right, data);
    } else { // the data is in the root
        Node* old = top;
        if (top->left == NULL) top = top->right;
        else if (top->right == NULL) top = top->left;
        else replace(old, old->left);
         
        delete old;
        return true;
    }
}

void BST::replace(Node*& old, Node*& top)
{
    if (top->right) replace(old, top->right);
    else {
        old->data = top->data;
        old = top;
        top = top->left;
    }
}

Node* BST::getRootNode()
{
    return root;
}

bool BST::add(int data)
{
    return addr(root, data);
}

bool BST::remove(int data)
{
    return remover(root, data);
}

void BST::clear()
{
    while (root != NULL) {
        remove(root->data);
    }
}

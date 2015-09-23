// Written by Aleks Christensen

#include "Node.h"

Node::Node(int dataIn, Node* leftP, Node* rightP) : data(dataIn), 
    left(leftP), right(rightP), bal(0), inc(false), dec(false) {}
Node::~Node(){}

int Node::height(Node* lroot)
{
    if (lroot == NULL) return 0;
    else
    {
        int l = height(lroot->left);
        int r = height(lroot->right);
        return 1 + max(l, r);
    }
}

int Node::getData()
{
    return data;
}

Node* Node::getLeftChild()
{
    return left;
}

Node* Node::getRightChild()
{
    return right;
}

int Node::getHeight()
{
    if (left == NULL && right == NULL) return 1;
    else {
        int l, r;
        left ? l = left->getHeight() : l = 0;
        right ? r = right->getHeight() : r = 0;
        return 1 + max(l, r);
    }
}

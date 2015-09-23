#include "Node.h"

Node::Node(int dataIn = -1, Node* leftPtr = NULL, Node* rightPtr = NULL) : NodeInterface()
{
    data = dataIn;
    left = leftPtr;
    right = rightPtr;
}

Node::~Node(){}

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

/*bool Node::addLeftChild(int data)
{
    if (left) return false;
    else {
        Node* left = new Node(data);
        return true;
    }
}

bool Node::addRightChild(int data)
{
    if (right) return false;
    else {
        Node* right = new Node(data);
        return true;
    }
}*/

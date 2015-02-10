// Written by Aleks Christensen

#ifndef NODE_H_
#define NODE_H_

#include <cstddef>

template <class T>
struct Node
{
    // Data of node
    T data;
    // Next node in list
    Node* next;

    Node(const T& dataItem, Node* nextPtr = NULL) :
        data(dataItem), next(nextPtr) {};
};

#endif

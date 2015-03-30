// Written by Aleks Christensen

#ifndef NODE_H_
#define NODE_H_

#include "NodeInterface.h"
#include <cstddef>

class Node : public NodeInterface
{
    private:
        // Data of node
        //int data;

        // Left child of node
        //Node* left;

        // Right child of node
        //Node* right;

    public:

        // Data of node
        int data;

        // Left child
        Node* left;

        // Right child
        Node* right;

        Node(int dataIn, Node* leftPtr, Node* rightPtr);
        ~Node();

        /*
         * Returns the data that is stored in the node
         */
        int getData();

        /*
         * Returns the left child of this node or null if none
         */
        Node* getLeftChild();

        /*
         * Returns the right child of this node or null if none
         */
        Node* getRightChild();

        /*
         * Adds left child to node
         * Returns true if successful, false otherwise (already has child)
         */
        //bool addLeftChild(int data);

        /*
         * Adds right child to node
         * Returns true if successful, false otherwise (already has child)
         */
        //bool addRightChild(int data);
};

#endif

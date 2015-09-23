// Written by Aleks Christensen

#ifndef NODE_H_
#define NODE_H_

#include <cstddef>
#include "NodeInterface.h"

class Node : public NodeInterface
{
    private:
        
        int height(Node* lroot);

    public:
        // Left child
        Node* left;
        // Right child
        Node* right;
        // Data in node
        int data;
        // Balance of subtree
        int bal;
        // Has the height increased?
        bool inc;
        // Has the height decreased?
        bool dec;


        Node(int dataIn, Node* leftP, Node* rightP);
        ~Node();

        //int diff(Node* lroot);

        /*
         * Returns data stored in node
         */
        int getData();

        /*
         * Returns left child of node or null if empty
         */
        Node* getLeftChild();

        /*
         * Returns right child of node or null if empty
         */
        Node* getRightChild();

        /*
         * Returns height of this node. Height is number of nodes
         * along the longest path from this node to a leaf.
         */
        int getHeight();
};

#endif

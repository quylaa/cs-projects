// Written by Aleks Christensen

#ifndef AVL_H_
#define AVL_H_

#include "AVLInterface.h"
#include "Node.h"

class AVL : public AVLInterface
{
    private:
        // root node of tree
        Node* root;

        // Private add function
        bool addn(int data, Node*& lroot);

        // Private remove function
        bool removen(int data, Node*& lroot);

        void replace(Node*& lroot, Node*& nroot);

        // Rotate right
        Node* rotR(Node* lroot);

        // Rotate left
        Node* rotL(Node* lroot);

        // Right-right rotation
        Node* RR(Node* lroot);
        
        // Right-left rotation
        Node* RL(Node* lroot);

        // Left-right rotation
        Node* LR(Node* lroot);

        // Left-left rotation
        Node* LL(Node* lroot);

        // Balance tree
        Node* balance(Node* lroot);

        int diff(Node* lroot);

    public:

        AVL();
        ~AVL();

        /*
         * Returns root node of tree
         */
        Node* getRootNode();

        /*
         * Attempts to add given int to tree
         * Rebalances tree if data successfully added
         */
        bool add(int data);

        /*
         * Attempts to remove given int from tree
         * Rebalances tree if successfully removed
         */
        bool remove(int data);
};

#endif

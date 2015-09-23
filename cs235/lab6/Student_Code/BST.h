// Written by Aleks Christensen

#ifndef BST_H_
#define BST_H_

#include "BSTInterface.h"
#include "Node.h"

class BST : public BSTInterface
{
    private:
        // Root node of tree
        Node* root;

    public:
        
        //Node* root;

        BST();

        ~BST();

        /*
         * Returns root node for the tree
         */
        Node* getRootNode();

        /*
         * Attempts to add given int to tree
         *
         * returns true if added
         * returns false if unsuccessfull (duplicate)
         */
        bool add(int data);

        /*
         * Attempts to remove given int from tree
         *
         * returns true if removes
         * returns false if unremovable (not present)
         */
        bool remove(int data);

        /*
         * Removes all nodes from tree, giving empty tree
         */
        void clear();



        bool addr(Node*& top, int data);

        bool remover(Node*& top, int data);

        void replace(Node*& old, Node*& top);
};

#endif

// Written by Aleks Christensen

#ifndef LIST_DEF_
#define LIST_DEF_

#include "Node.h"
#include <string>

template<class T>
class List : public LinkedListInterface
{
    private:
        // Initial size of list
        static const size_t INIT_SIZE = 10;
        // Number of items in list
        size_t numItems;
        // Total size of list
        size_t listSize;
        // List itself
        T* list;


    public:
        
        List<T>(void): listSize(INIT_SIZE), list(new T[INIT_SIZE]), numItems(0) {};
        virtual ~List<T>(void){};


        /*
         * insertHead
         * A node with given value is inserted at beginning of list
         * Do not allow duplicate values
         */
        void insertHead(T value);

        /*
         * insertTail
         * A node with given value is inserted at end of list
         * Do not allow duplicate values
         */
        void insertTail(T value);

        /*
         * insertAfter
         * A node with given value is inserted immediately after the node
         * with value insertionNode.
         * Only add if the node with value insertionNode is in list.
         * Do not allow duplicate values
         */
        void insertAfter(T value, T insertionNode);

        /*
         * remove
         * The node with given value is removed from list
         * The list may or may not have node with given value
         */
        void remove(T value);

        /*
         * clear
         * Remove all nodes from list
         */
        void clear();

        /*
         * at
         * Return value of node at given index. List begins at index 0.
         * If given index is out of range of list, throw out-of-range exception
         */
        T at(int index);

        /*
         * size
         * Return number of nodes in list
         */
        int size();
};

#endif








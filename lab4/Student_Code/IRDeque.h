// Written by Aleks Christensen

#ifndef IRDeque_H_
#define IRDeque_H_

#include <cstddef>

class IRDeque
{
    private:
        
        struct Node
        {
            // Data in node
            int data;
            // previous node in list
            Node* prev;
            // next node in list
            Node* next;

            Node(const int& dataItem, Node* prevPtr = NULL, Node* nextPtr = NULL) :
                data(dataItem), prev(prevPtr), next(nextPtr) {};
        };

        // top of list
        Node* top;
        // bottom of list
        Node* bottom;

    public:

        IRDeque();
        ~IRDeque();

        int showTop();
        
        int showBottom();

        bool empty();

        bool dupe(int val);

        Node* find(int val);

        Node* prevNode(int val);

        void pushTop(int val);

        void remove(int val);

        void popTop();

        void popBottom();

        void clear();

        int size();
};

#endif

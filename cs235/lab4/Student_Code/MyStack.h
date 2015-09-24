// Written by Aleks Christensen

#ifndef MYSTACK_H_
#define MYSTACK_H_

#include <cstddef>

class MyStack
{
    private:
        
        struct Node
        {
            // Data in node
            int data;
            // next node in list
            Node* next;

            Node(const int& dataItem, Node* nextPtr = NULL) :
                data(dataItem), next(nextPtr) {};
        };

        // top of list
        Node* top;

    public:

        MyStack();
        ~MyStack();

        int showTop();

        bool empty();

        bool dupe(int val);

        Node* find(int val);

        void push(int val);

        void pop();

        void clear();

        int size();
};

#endif

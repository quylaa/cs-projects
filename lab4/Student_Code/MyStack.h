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

        MyStack() : top(NULL) {};
        ~MyStack(){clear();};

        int showTop()
        {
            return top->data;
        };

        bool empty()
        {
            if (size() == 0) return true;
            else return false;
        };

        bool dupe(int val)
        {
            Node* cur = top;
            while (cur != NULL)
            {
                if (cur->data == val) return true;
                cur = cur->next;
            }
            return false;
        };

        Node* find(int val)
        {
            if (top != NULL) {
                Node* cur = top;
                while (cur->data != val) {
                    if (cur->next == NULL) return NULL;
                    cur = cur->next;
                }
                return cur;
            } else return NULL;
        };

        void push(int val)
        {
            if (!dupe(val))
            {
                Node* newTop = new Node(val, top);
                top = newTop;
            }
        };

        void pop()
        {
            if (top != NULL)
            {
                Node* temp = top;
                top = top->next;
                delete temp;
            }
        };

        void clear()
        {
            while (top != NULL)
            {
                pop();
            }
        };

        int size()
        {
            if (top != NULL)
            {
                Node* cur = top;
                int i = 1;
                while (cur->next != NULL)
                {
                    cur = cur->next;
                    i++;
                }
                return i;
            } else return 0;
        };
};

#endif

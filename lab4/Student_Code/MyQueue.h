// Written by Aleks Christensen

#ifndef MYQUEUE_H_
#define MYQUEUE_H_

#include <cstddef>

class MyQueue
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

        MyQueue() : top(NULL), bottom(NULL) {};
        ~MyQueue(){clear();};

        int showTop()
        {
            return top->data;
        };
        
        int showBottom()
        {
            return bottom->data;
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

        Node* prevNode(int val)
        {
            Node* cur = find(val);
            if (cur != NULL) return cur->prev;
            else return NULL;
        };

        void pushTop(int val)
        {
            if (!dupe(val))
            {
                Node* newTop = new Node(val, NULL, top);
                top = newTop;
                if (bottom == NULL) bottom = newTop;
            }
        };

        void pushBottom(int val)
        {
            if (!dupe(val))
            {
                Node* newBottom = new Node(val, bottom, NULL);
                if (top == NULL)
                {
                    top = newBottom;
                    bottom = newBottom;
                } else 
                {
                    bottom->next = newBottom;
                    bottom = bottom->next;
                }
            }
        };

        void remove(int val)
        {
            Node* toDie = find(val);
            if (toDie)
            {
                if (toDie == top)
                {
                    top = top->next;
                    delete toDie;
                } else if (toDie == bottom)
                {
                    bottom = bottom->prev;
                    delete toDie;
                } else
                {
                    toDie->prev->next = toDie->next;
                    toDie->next->prev = toDie->prev;
                    delete toDie;
                }
            }
        };

        void popTop()
        {
            if (top != NULL)
            {
                Node* temp = top;
                top = top->next;
                delete temp;
            }
        };

        void popBottom()
        {
            if (bottom != NULL)
            {
         //       if (bottom == top)
         //       {
         //           delete bottom;
         //           bottom = NULL;
         //           top = NULL;
         //       }
                Node* temp = bottom;
                bottom = bottom->prev;
                //bottom->next = NULL;
                delete temp;
            }
        };

        void clear()
        {
            while (top != NULL)
            {
                popTop();
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

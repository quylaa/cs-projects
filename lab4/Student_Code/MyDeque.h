// Written by Aleks Christensen

#ifndef MYDEQUE_H_
#define MYDEQUE_H_

#include <cstddef>

class MyDeque
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

        MyDeque() : top(NULL), bottom(NULL) {};
        ~MyDeque(){clear();};

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
                if (top == NULL) top = newTop;
                else
                {
                    top->prev = newTop;
                    top = newTop;
                }
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
                    //bottom = bottom->prev;
                    //delete toDie;
                    Node* cur = top;
                    while (cur != NULL)
                    {
                        cout << cur->data << "->";
                        if (cur->next == bottom)
                        {
                            bottom = cur;
                            delete toDie;
                        }
                        cur = cur->next;
                    }
                    cout << endl;
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
                //Node* temp = top;
                //top = top->next;
                //delete temp;
                remove(top->data);
            }
        };

        void popBottom()
        {
            if (bottom != NULL)
            {
                //Node* temp = bottom;
                //bottom = bottom->prev;
                //delete temp;
                remove(bottom->data);
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
                    /*if (cur->data > 1000)
                    {
                        remove(cur->data);
                        continue;
                    }*/
                    cur = cur->next;
                    i++;
                }
                return i;
            } else return 0;
        };
};

#endif

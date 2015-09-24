<<<<<<< HEAD
// Written by Aleks Christensen

#ifndef LIST_H_
#define LIST_H_

#include <cstddef>
#include "LinkedListInterface.h"
//#include <string>

template<typename T> 
class List : public LinkedListInterface<T>
{
    private:

        struct Node
        {
            // Data of node
            T data;
            // Next node in list
            Node* next;

            Node(const T& dataItem, Node* nextPtr = NULL) :
                data(dataItem), next(nextPtr) {};
        };


        // Initial size of list
        //static const size_t INIT_SIZE = 10;
        // Number of items in list
        size_t numItems;
        // Total size of list
        //size_t listSize;
        // List itself
        //T* list;
        // Head of list
        Node* head;


    public:
        
        List<T>(void);
        virtual ~List<T>(void);


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

=======
// Written by Aleks Christensen

#ifndef LIST_H_
#define LIST_H_

#include <cstddef>
#include <stdexcept>
#include "LinkedListInterface.h"

template<typename T> 
class List : public LinkedListInterface<T>
{
    private:

        struct Node
        {
            // Data of node
            T data;
            // Next node in list
            Node* next;

            Node(const T& dataItem, Node* nextPtr = NULL) :
                data(dataItem), next(nextPtr) {};
        };

        // Head of list
        Node* head;
        // End of list
        Node* tail;


    public:
        
        List<T>(void) : head(NULL), tail(NULL) {};
        ~List<T>(void){clear();};


        bool dupe(T value)
        {
            Node* cur = head;
            while (cur != NULL) {
                if (cur->data == value) {
                   return true;
                }
                cur = cur->next;
           }
            return false;
        };

        Node* find(T value)
        {
            if (head != NULL) {
                Node* cur = head;
                while (cur->data != value) {
                    if (cur->next == NULL) return NULL;
                    cur = cur->next;
                }
                return cur;
            }
            else return NULL;
        };

        Node* prev(T value)
        {
            if (head != NULL) {
                Node* cur = head;
                Node* nx = head->next;
                while (nx->data != value) {
                    if (nx->next == NULL) return NULL;
                    cur = cur->next;
                    nx = nx->next;
                }
                return cur;
            }
            else return NULL;
        };

        /*
         * insertHead
         * A node with given value is inserted at beginning of list
         * Do not allow duplicate values
         */
        void insertHead(T value)
        {
            if (!dupe(value)) {
                Node* newFirst = new Node(value, head);
                head = newFirst;
                if(tail == NULL) tail = newFirst;
            }
        };

        /*
         * insertTail
         * A node with given value is inserted at end of list
         * Do not allow duplicate values
         */
        void insertTail(T value)
        {
            if (!dupe(value)) {
               Node* newLast = new Node(value);
               if (head == NULL) {
                    head = newLast;
                    tail = newLast;
                } else {
                    tail->next = newLast;
                    tail = tail->next;
                }
            }
        };

        /*
         * insertAfter
         * A node with given value is inserted immediately after the node
         * with value insertionNode.
         * Only add if the node with value insertionNode is in list.
         * Do not allow duplicate values
         */
        void insertAfter(T value, T insertionNode)
        {
            if (!dupe(value)) {
                Node* prv = find(insertionNode);
                if (prv != NULL) {
                    Node* nx = prv->next;
                    if (nx == NULL) {
                        insertTail(value);
                    } else {
                        Node* newNode = new Node(value, nx);
                        prv->next = newNode;
                    }
                }
            }
        };

        /*
         * remove
         * The node with given value is removed from list
         * The list may or may not have node with given value
         */
        void remove(T value)
        {
            Node* toDie = find(value);
            if (toDie) {
                if (toDie == head) {
                    Node* temp = toDie;
                    head = head->next;
                    delete toDie;
                } else {
                    Node* prv = prev(value);
                    Node* nx = toDie->next;
                    prv->next = nx;
                    delete toDie;
                }
            }
        };

        /*
         * clear
         * Remove all nodes from list
         */
        void clear()
        {
            while (head != NULL) {
                remove(head->data);
            }
        };

        /*
         * at
         * Return value of node at given index. List begins at index 0.
         * If given index is out of range of list, throw out-of-range exception
         */
        T at(int index)
        {
            if (index >= 0) {
                if (head != NULL) {
                    if (index < size()) {
                        Node* cur = head;
                        for (int i = 0; i < index; i++) {
                            cur = cur->next;
                        }
                        T val = cur->data;
                        return val;
                    } else throw out_of_range("err");
                } else throw out_of_range("err");
            } else throw out_of_range("err");
        };

        /*
         * size
         * Return number of nodes in list
         */
        int size()
        {
            if (head != NULL) {
                Node* cur = head;
                int num = 1;
                while (cur->next != NULL) {
                    cur = cur->next;
                    num++;
                }
                tail = cur;
                tail->next = NULL;
                return num;
            } else return 0;
        };
};

#endif

>>>>>>> dbca4aa834afce736adf02a4922e011aab207d35

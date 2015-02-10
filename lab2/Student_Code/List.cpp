// Written by Aleks Christensen

#include <stdexcept>
//#include "LinkedListInterface.h"
#include "List.h"
//#include "Node.h"

template <typename T> List<T>::List() : numItems(0), head(new Node(0)) {}
/*{
    //listSize = 0;
    numItems = 0;

    Node* head = new Node("head");
    //numItems++;
}*/
template <typename T> List<T>::~List<T>(void){}

template <typename T> void List<T>::insertHead(T value)
{
    //if (numItems == 0) {
    //    list[0] = new Node::Node("head");
    //    numItems++;
    //}
    bool dupe = false;
    //for (size_t i = 0; i < ; i++) {
    //    if (list[i]->data == value) {
    //        dupe = true;
    //    }
    //}
    Node* cur = head;
    while (cur != NULL) {
        if (cur->data == value) {
            dupe = true;
        }
        cur = cur->next;
    }
    if (!dupe) {
        //if (numItems == listSize) {
        //    T* newList[listSize * 2];
        //    for (size_t j = 0; j < (listSize * 2); j++) {
        //        newList[j] = list[j];
        //    }
        //    delete list;
        //    Node* list = newList;
        //    delete newList;
        //    listSize *= 2;
        //}
        Node* newFirst = new Node(value, head->next);
        head->next = newFirst;
        numItems++;
    }
    delete cur;
}

template <typename T> void List<T>::insertTail(T value)
{
    /*if (numItems == 0) {
        list[0] = new Node("head");
        numItems++;
    }*/
    bool dupe = false;
    /*for (size_t i = 0; i < sizeof(list); i++) {
        if (list[i]->data == value) {
            dupe = true;
        }
    }*/
    Node* cur = head;
    while (cur != NULL) {
        if (cur->data == value) {
            dupe = true;
        }
        cur = cur->next;
    }
    delete head;
    if (!dupe) {
        /*if (numItems == listSize) {
            T* newList[listSize * 2];
            for (size_t j = 0; j < (listSize * 2); j++) {
                newList[j] = list[j];
            }
            delete list;
            Node* list = newList;
            delete newList;
            listSize *= 2;
        }*/
    Node* newLast = new Node(value);
    Node* tail = head;
    for (size_t i = 1; i <= numItems; i++) {
        tail = tail->next;
    }
    tail->next = newLast;
    numItems++;
    delete tail;
    delete newLast;
    }
}

template <typename T> void List<T>::insertAfter(T value, T insertionNode)
{
    /*if (numItems == 0) {
        list[0] = new Node("head");
        numItems++;
    }*/
    bool dupe = false;
    /*int ins = -1;
    for (size_t i = 0; i < sizeof(list); i++) {
        if (list[i]->data == value) {
            dupe = true;
        }
        if (list[i]->data == insertionNode) {
            ins = 0;
        }
    }*/
    Node* cur = head;
    Node* ins = head;
    while (cur != NULL) {
        if (cur->data == value) {
            dupe = true;
        }
        if (cur->data == insertionNode) {
            ins = cur;
        }
        cur = cur->next;
    }
    delete cur;
    if (!dupe) {
        /*if (numItems == listSize) {
            T* newList[listSize * 2];
            for (size_t j = 0; j < (listSize * 2); j++) {
                newList[j] = list[j];
            }
            delete list;
            Node* list = newList;
            delete newList;
            listSize *= 2;
        }
        if (ins >= 0) {
            list[numItems] = new Node(value, list[ins + 1]);
            list[ins]->next = list[numItems];
            numItems++;
        }*/
        if (ins != head) {
            Node* newNode = new Node(value, ins->next);
            ins->next = newNode;
            delete newNode;
            delete ins;
            numItems++;
        }
    }
}

template <typename T> void List<T>::remove(T value)
{
    /*for (size_t i = 0; i < numItems; i++) {
        if (list[i]->data == value) {
            list[i - 1]->next = list[i + 1];
            list[i] = list[numItems];
            delete list[numItems];
            numItems--;
        }
    }*/
    Node* cur = head;
    while (cur != NULL) {
        if (cur->data == head->data) {
            break;
        }
        if (cur->next->data == value) {
            if (cur->next->next == NULL) {
                cur->next = NULL;
                delete cur->next;
            } else {
                cur->next = cur->next->next;
                delete cur->next;
            }
        }
    }
    delete cur;

}

template <typename T> void List<T>::clear()
{
    /*delete list;
    list(new T[INIT_SIZE]);
    numItems = 0;
    listSize = INIT_SIZE;*/
    Node* cur = head->next;
    while (cur->data != head->data) {
        if (cur->next->next == NULL) {
            cur->next == NULL;
            delete cur->next->next;
            cur = head->next;
        }
        cur = cur->next;
    }
}

template <typename T> T List<T>::at(int index)
{
    if (index < 0 || index > numItems) {
        throw std::out_of_range("err");
    } else {
        Node* cur = head;
        for (size_t i = 0; i < numItems; i++) {
            if (i == index) {
                return cur->data;
            }
            cur = cur->next;
        }
    }
}

template <typename T> int List<T>::size()
{
    return numItems;
}
            
template class List<int>;
template class List<string>;





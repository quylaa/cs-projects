// Written by Aleks Christensen

#include "List.h"
#include "Node.h"

template <class T> void List<T>::List(void) : LinkedListInterface(void){}
template <class T> void List<T>::~List<T>(void){ delete list[]; }

template <class T> void List<T>::insertHead(T value)
{
    if (numItems == 0) {
        list[0] = new Node("head");
        numItems++;
    }
    bool dupe = false;
    for (size_t i = 0; i < sizeof(list); i++) {
        if (list[i]->data == value) {
            dupe = true;
        }
    }
    if (!dupe) {
        if (numItems == listSize) {
            T* newList[listSize * 2];
            for (size_t j = 0; j < (listSize * 2); j++) {
                newList[j] = list[j];
            }
            delete list[];
            list[] = newList;
            delete newList[];
            listSize *= 2;
        }
        list[numItems] = new Node(value, list[1]);
        list[0]->next = list[numItems];
        numItems++;
    }
}

template <class T> void List<T>::insertTail(T value)
{
    if (numItems == 0) {
        list[0] = new Node("head");
        numItems++;
    }
    bool dupe = false;
    for (size_t i = 0; i < sizeof(list); i++) {
        if (list[i]->data == value) {
            dupe = true;
        }
    }
    if (!dupe) {
        if (numItems == listSize) {
            T* newList[listSize * 2];
            for (size_t j = 0; j < (listSize * 2); j++) {
                newList[j] = list[j];
            }
            delete list[];
            list[] = newList;
            delete newList[];
            listSize *= 2;
        }
    list[numItems] = new Node(value);
    list[numItems - 1]->next = list[numItems];
    numItems++;
    }
}

template <class T> void List<T>::insertAfter(T value, T insertionNode)
{
    if (numItems == 0) {
        list[0] = new Node("head");
        numItems++;
    }
    bool dupe = false;
    int ins = -1;
    for (size_t i = 0; i < sizeof(list); i++) {
        if (list[i]->data == value) {
            dupe = true;
        }
        if (list[i]->data == insertionNode) {
            ins = 0;
        }
    }
    if (!dupe) {
        if (numItems == listSize) {
            T* newList[listSize * 2];
            for (size_t j = 0; j < (listSize * 2); j++) {
                newList[j] = list[j];
            }
            delete list[];
            list[] = newList;
            delete newList[];
            listSize *= 2;
        }
        if (ins >= 0) {
            list[numItems] = new Node(value, list[ins + 1]);
            list[ins]->next = list[numItems];
            numItems++;
        }
    }
}

template <class T> void List<T>::remove(T value)
{
    for (size_t i = 0; i < numItems; i++) {
        if (list[i]->data == value) {
            list[i - 1]->next = list[i + 1];
            list[i] = list[numItems];
            delete list[numItems];
            numItems--;
        }
    }
}

template <class T> void List<T>::clear()
{
    delete list[];
    list(new T[INIT_SIZE]);
    numItems = 0;
    listSize = INIT_SIZE;
}

template <class T> T List<T>::at(int index)
{
    if (index < 0 || index > numItems) {
        throw out_of_range("err");
    } else {
        return list[index]->data;
    }
}

template <class T> int List<T>::size()
{
    return numItems;
}
            






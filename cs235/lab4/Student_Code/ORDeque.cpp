// Written by Aleks Christensen

#include <iostream>
#include "ORDeque.h"

ORDeque::ORDeque() 
{
 top = NULL; 
 bottom = NULL;
}

ORDeque::~ORDeque()
{
    clear();
}

int ORDeque::showTop()
{
    return top->data;
}

int ORDeque::showBottom()
{
    return bottom->data;
}

bool ORDeque::empty()
{
    if (size() == 0) return true;
    else return false;
}

bool ORDeque::dupe(int val)
{
    Node* cur = top;
    while (cur != NULL)
    {
        if (cur->data == val) return true;
        cur = cur->next;
    }
    return false;
}

ORDeque::Node* ORDeque::find(int val)
{
    if (top != NULL) {
        Node* cur = top;
        while (cur->data != val) {
            if (cur->next == NULL) return NULL;
            cur = cur->next;
        }
        return cur;
    } else return NULL;
}

ORDeque::Node* ORDeque::prevNode(int val)
{
    Node* cur = find(val);
    if (cur != NULL) return cur->prev;
    else return NULL;
}

void ORDeque::pushTop(int val)
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
}

void ORDeque::pushBottom(int val)
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
            bottom = newBottom;
        }
    }
}

void ORDeque::remove(int val)
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
            bottom->next = NULL;
            delete toDie;
        } else
        {
            toDie->prev->next = toDie->next;
            toDie->next->prev = toDie->prev;
            delete toDie;
        }
    }
}

void ORDeque::popTop()
{
    if (top != NULL)
    {
        remove(top->data);
    }
}

void ORDeque::clear()
{
    while (top != NULL)
    {
        popTop();
    }
}

int ORDeque::size()
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
}
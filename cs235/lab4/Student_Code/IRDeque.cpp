// Written by Aleks Christensen

#include "IRDeque.h"

IRDeque::IRDeque() 
{
 top = NULL; 
 bottom = NULL;
}

IRDeque::~IRDeque()
{
    clear();
}

int IRDeque::showTop()
{
    return top->data;
}

int IRDeque::showBottom()
{
    return bottom->data;
}

bool IRDeque::empty()
{
    if (size() == 0) return true;
    else return false;
}

bool IRDeque::dupe(int val)
{
    Node* cur = top;
    while (cur != NULL)
    {
        if (cur->data == val) return true;
        cur = cur->next;
    }
    return false;
}

IRDeque::Node* IRDeque::find(int val)
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

IRDeque::Node* IRDeque::prevNode(int val)
{
    Node* cur = find(val);
    if (cur != NULL) return cur->prev;
    else return NULL;
}

void IRDeque::pushTop(int val)
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

void IRDeque::remove(int val)
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

void IRDeque::popTop()
{
    if (top != NULL)
    {
        remove(top->data);
    }
}

void IRDeque::popBottom()
{
    if (bottom != NULL)
    {
        remove(bottom->data);
    }
}

void IRDeque::clear()
{
    while (top != NULL)
    {
        popTop();
    }
}

int IRDeque::size()
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
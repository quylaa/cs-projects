// Written by Aleks Christensen

#include "MyDeque.h"

MyDeque::MyDeque() 
{
 top = NULL; 
 bottom = NULL;
}

MyDeque::~MyDeque()
{
    clear();
}

int MyDeque::showTop()
{
    return top->data;
}

int MyDeque::showBottom()
{
    return bottom->data;
}

bool MyDeque::empty()
{
    if (size() == 0) return true;
    else return false;
}

bool MyDeque::dupe(int val)
{
    Node* cur = top;
    while (cur != NULL)
    {
        if (cur->data == val) return true;
        cur = cur->next;
    }
    return false;
}

MyDeque::Node* MyDeque::find(int val)
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

MyDeque::Node* MyDeque::prevNode(int val)
{
    Node* cur = find(val);
    if (cur != NULL) return cur->prev;
    else return NULL;
}

void MyDeque::pushTop(int val)
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

void MyDeque::pushBottom(int val)
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
}

void MyDeque::remove(int val)
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

void MyDeque::popTop()
{
    if (top != NULL)
    {
        remove(top->data);
    }
}

void MyDeque::popBottom()
{
    if (bottom != NULL)
    {
        remove(bottom->data);
    }
}

void MyDeque::clear()
{
    while (top != NULL)
    {
        popTop();
    }
}

int MyDeque::size()
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
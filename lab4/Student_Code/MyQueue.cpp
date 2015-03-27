// Written by Aleks Christensen

#include "MyQueue.h"

MyQueue::MyQueue()
{
    top = NULL;
    bottom = NULL;
}

MyQueue::~MyQueue()
{
    clear();
}

int MyQueue::showTop()
{
    return top->data;
}

int MyQueue::showBottom()
{
    return bottom->data;
}

bool MyQueue::empty()
{
    if (size() == 0) return true;
    else return false;
}

bool MyQueue::dupe(int val)
{
    Node* cur = top;
    while (cur != NULL)
    {
        if (cur->data == val) return true;
        cur = cur->next;
    }
    return false;
}

MyQueue::Node* MyQueue::find(int val)
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

MyQueue::Node* MyQueue::prevNode(int val)
{
    Node* cur = find(val);
    if (cur != NULL) return cur->prev;
    else return NULL;
}

void MyQueue::pushTop(int val)
{
    if (!dupe(val))
    {
        Node* newTop = new Node(val, NULL, top);
        top = newTop;
        if (bottom == NULL) bottom = newTop;
    }
}

void MyQueue::pushBottom(int val)
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

void MyQueue::remove(int val)
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
}

void MyQueue::popTop()
{
    if (top != NULL)
    {
        Node* temp = top;
        top = top->next;
        delete temp;
    }
}

void MyQueue::popBottom()
{
    if (bottom != NULL)
    {
        Node* temp = bottom;
        bottom = bottom->prev;
        delete temp;
    }
}

void MyQueue::clear()
{
    while (top != NULL)
    {
        popTop();
    }
}

int MyQueue::size()
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

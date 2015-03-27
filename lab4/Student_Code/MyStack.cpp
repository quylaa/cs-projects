// Written by Aleks Christensen

#include "MyStack.h"

MyStack::MyStack()
{
    top = NULL;
}

MyStack::~MyStack()
{
    clear();
}

int MyStack::showTop()
{
    return top->data;
}

bool MyStack::empty()
{
    if (size() == 0) return true;
    else return false;
}

bool MyStack::dupe(int val)
{
    Node* cur = top;
    while (cur != NULL)
    {
        if (cur->data == val) return true;
        cur = cur->next;
    }
    return false;
}

MyStack::Node* MyStack::find(int val)
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

void MyStack::push(int val)
{
    if (!dupe(val))
    {
        Node* newTop = new Node(val, top);
        top = newTop;
    }
}

void MyStack::pop()
{
    if (top != NULL)
    {
        Node* temp = top;
        top = top->next;
        delete temp;
    }
}

void MyStack::clear()
{
    while (top != NULL)
    {
        pop();
    }
}

int MyStack::size()
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

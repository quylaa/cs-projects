// Written by Aleks Christensen

#include "Circ.h"

Circ::Circ()
{
    head = NULL;
    tail = NULL;
}

Circ::~Circ(){clear();}

bool Circ::check(string name)
{
    if (Circ::empty()) return false;
    else
    {
        if (head != NULL)
        {
            Node* cur = head;
            while (cur != NULL)
            {
                if (cur->data == name) return true;
                cur = cur->next;
            }
        } else return false;
    }
}


bool Circ::insertHead(string name)
{
    if (check(name)) return false;
    else
    {
        Node* newHead = new Node(name, NULL, head);
        head->prev = newHead;
        head = newHead;
        return true;
    }
}

bool Circ::insertTail(string name)
{
    if (check(name)) return false;
    else
    {
        Node* newTail = new Node(name, tail, NULL);
        tail->next = newTail;
        tail = newTail;
        return true;
    }
}

bool Circ::insertAt(string name, int index)
{
    if (check(name)) return false;
    else if (index < 0 || Circ::size() <= index) return false;
    else
    {
        if (index == 0)
        {
            if (Circ::insertHead()) return true;
        } else if (index == Circ::size() - 1)
        {
            if (Circ::insertTail()) return true;
        } else
        {
            Node* newItem = new Node(name, NULL, NULL);
            Node* cur = head->next;
            for (int i = 1; i < Circ::size(); i++)
            {
                if (i == index)
                {
                    newItem->prev = cur->prev;
                    newItem->next = cur;
                    return true;
                }
                cur = cur->>next;
            }
        }
    }
}

bool Circ::removeHead()
{
    if (Circ::empty()) return false;
    else
    {
        if (head->next)
        {
            Node* tmp = head;
            head = head->next;
            head->prev = NULL;
            delete tmp;
            if (Circ::size() == 1)
            {
                head = NULL;
                tail = NULL;
            }
        }
        else
        {
            delete head;
            head = NULL;
            tail = NULL;
        }
    }
}
            

bool Circ::empty()
{
    if (!Circ::size()) return true;
    else return false;
}

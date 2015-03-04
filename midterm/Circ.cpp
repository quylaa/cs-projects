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
        if (head == NULL)
        {
            Node* newHead = new Node(name, NULL, NULL);
            head = newHead;
            tail = newHead;
            return true;
        }
        else
        {
            Node* newHead = new Node(name, NULL, head);
            head->prev = newHead;
            head = newHead;
            return true;
        }
    }
}

bool Circ::insertTail(string name)
{
    if (check(name)) return false;
    else
    {
        if (tail == NULL)
        {
            Node* newTail = new Node(name, NULL, NULL);
            head = newTail;
            tail = newTail;
            return true;
        } else
        {
            Node* newTail = new Node(name, tail, NULL);
            tail->next = newTail;
            tail = newTail;
            return true;
        }
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
            if (Circ::insertHead(name)) return true;
        } else if (index == Circ::size() - 1)
        {
            if (Circ::insertTail(name)) return true;
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
                cur = cur->next;
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

bool Circ::removeTail()
{
    if (Circ::empty()) return false;
    else
    {
        Node* tmp = tail;
        tail = tail->prev;
        tail->next = NULL;
        delete tmp;
        if (Circ::size() == 1)
        {
            head = NULL;
            tail = NULL;
        }
    }
}

bool Circ::removeAt(int index)
{
    if (Circ::empty()) return false;
    else if (index < 0 || Circ::size() <= index) return false;
    else
    {
        if (index == 0)
        {
            if (Circ::removeHead()) return true;
        }
        else if (index == Circ::size() - 1)
        {
            if (Circ::removeTail()) return true;
        }
        else
        {
            Node* cur = head->next;
            for (int i = 1; i < (Circ::size() - 1); i++)
            {
                if (index == i)
                {
                    cur->prev->next = cur->next;
                    cur->next->prev = cur->prev;
                    delete cur;
                    return true;
                }
                cur = cur->next;
            }
        }
    }
}

void Circ::clear()
{
    if (!Circ::empty())
    {
        while (head != NULL)
        {
            Circ::removeHead();
        }
    }
}

int Circ::size()
{
    Node* cur = head;
    int size = 1;
    while (cur != tail)
    {
        size++;
        cur = cur->next;
    }
    return size + 1;
}

string Circ::atFromHead(int index)
{
    if (Circ::empty()) return "invalid";
    else if (index < 0 || Circ::size() <= index) return "invalid";
    else
    {
        if (index == 0) return head->data;
        else if (index == (Circ::size() - 1)) return tail->data;
        else
        {
            Node* cur = head->next;
            for (int i = 1; i < (Circ::size() - 1); i++)
            {
                if (index == i) return cur->data;
                cur = cur->next;
            }
        }
    }
}

string Circ::atFromTail(int index)
{
    if (Circ::empty()) return "invalid";
    else if (index < 0 || Circ::size() <= index) return "invalid";
    else
    {
        if (index == 0) return tail->data;
        else if (index == (Circ::size() - 1)) return head->data;
        else
        {
            Node* cur = tail->prev;
            for (int i = 1; i < (Circ::size() - 1); i++)
            {
                if (index == i) return cur->data;
                cur = cur->prev;
            }
        }
    }
}

bool Circ::empty()
{
    if (!Circ::size()) return true;
    else return false;
}

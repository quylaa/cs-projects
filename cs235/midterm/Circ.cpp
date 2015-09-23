// Written by Aleks Christensen

#include "Circ.h"

Circ::Circ()
{
    head = NULL;
    tail = NULL;
    srand(time(0));
}

Circ::~Circ(){clear();}

Circ::Node* Circ::find(int index)
{
    if (Circ::empty()) return NULL;
    else
    {
        Node* cur = head;
        for (int i = 0; i < Circ::size() - 1; i++)
        {
            if (i == index) return cur;
            cur = cur->next;
        }
    }
}

void Circ::linking()
{
    Node* cur = head;
    while (cur != tail)
    {
        cout << cur->prev->data << "<-" << cur->data << "->" << cur->next->data << endl;
        cur = cur->next;
    }
    cout << tail->prev->data << tail->data << "->" << tail->next->data << endl;
}

int Circ::getIndex(string name)
{
    if (Circ::empty()) return 0;
    else
    {
        Node* cur = head;
        for (int i = 0; i < (Circ::size() - 1); i++)
        {
            if (cur->data == name) return i;
            cur = cur->next;
        }
        if (tail->data == name) return (Circ::size() - 1);
    }
}

void Circ::shuffle()
{
    int s = Circ::size();
    for (int i = 0; i < (s - 1); i++)
    {
        int swap = rand() % s;
        if (swap == i) swap = rand() % s;
        string temp = Circ::find(i)->data;
        Node* first = Circ::find(i);
        Node* second = Circ::find(swap);
        //cout << "Swapping " << i << ": " << first->data << "\n with " << swap << ": " << second->data << endl;
        first->data = second->data;
        second->data = temp;
    }
}

bool Circ::check(string name)
{
    if (Circ::empty()) return false;
    else
    {
        if (head != NULL)
        {
            Node* cur = head;
            while (cur != tail)
            {
                if (cur->data == name) return true;
                cur = cur->next;
            }
            if (tail->data == name) return true;
        } else return false;
    }
}

string Circ::test(int count)
{
    Node* cur = head;
    while (Circ::size() > 1)
    {
        for (int i = 0; i < count; i++)
        {
            cur = cur->next;
        }
        // cur->prev->next = cur->next;
        // cur->next->prev = cur->prev;
        Circ::removeAt(Circ::getIndex(cur->data));
        // delete cur;
    }
    return cur->data;
}

string Circ::run(int count)
{
    Node* cur = head;
    while (Circ::size() > 1)
    {
        for (int i = 0; i < count; i++)
        {
            cur = cur->next;
        }
        cur->prev->next = cur->next;
        cur->next->prev = cur->prev;
        cout << "// Removed " << cur->data << " //" << endl;
        delete cur;
    }
    return cur->data;
}

bool Circ::insertHead(string name)
{
    if (check(name)) return false;
    else
    {
        if (head == NULL)
        {
            Node* newHead = new Node(name);
            head = newHead;
            if (tail == NULL) tail = newHead;
            // tail = newHead;
            return true;
        }
        else
        {
            Node* newHead = new Node(name, tail, head);
            head->prev = newHead;
            tail->next = newHead;
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
            Node* newTail = new Node(name);
            if (head == NULL) head = newTail;
            tail = newTail;
            return true;
        } else
        {
            Node* newTail = new Node(name, tail, head);
            tail->next = newTail;
            head->prev = newTail;
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
            Node* newItem = new Node(name);
            //Node* cur = head->next;
            Node* pos = Circ::find(index);
            newItem->prev = pos->prev;
            pos->prev->next = newItem;
            newItem->next = pos;
            pos->prev = newItem;
            return true;
            /*for (int i = 1; i < Circ::size(); i++)
            {
                if (i == index)
                {
                    newItem->prev = cur->prev;
                    newItem->next = cur;
                    return true;
                }
                cur = cur->next;
            }*/
        }
    }
}

bool Circ::removeHead()
{
    if (Circ::empty()) return false;
    else if (!head) return false;
    else
    {
        if (head->next)
        {
            Node* tmp = head;
            head = head->next;
            head->prev = tail;
            delete tmp;
            // if (Circ::size() == 1)
            // {
            //     head = NULL;
            //     tail = NULL;
            // }
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
    else if (!tail) return false;
    else
    {
        Node* tmp = tail;
        tail = tail->prev;
        tail->next = head;
        delete tmp;
        // if (Circ::size() == 1)
        // {
        //     head = NULL;
        //     tail = NULL;
        // }
    }
}

bool Circ::removeAt(int index)
{
    int s = Circ::size();
    if (Circ::empty()) return false;
    else if (index < 0 || s <= index) return false;
    else
    {
        if (index == 0)
        {
            if (Circ::removeHead()) return true;
        }
        else if (index == s - 1)
        {
            if (Circ::removeTail()) return true;
        }
        else
        {
            // Node* cur = head->next;
            // for (int i = 1; i < (s - 1); i++)
            // {
            //     if (index == i)
            //     {
            //         cur->prev->next = cur->next;
            //         cur->next->prev = cur->prev;
            //         delete cur;
            //         return true;
            //     }
            //     cur = cur->next;
            // }
            Node* toDie = Circ::find(index);
            toDie->prev->next = toDie->next;
            toDie->next->prev = toDie->prev;
            delete toDie;
            return true;
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
    //if (!head) return 0;
    //else if (!head->next) return 1;
    //else
    //{
        Node* cur = head;
        if (!cur) return 0;
        int size = 1;
        while (cur->next != head)
        {
            size++;
            if (!cur->next) break;
            cur = cur->next;
        }
        return size;
    //}
}

string Circ::atFromHead(int index)
{
    int s = Circ::size();
    if (Circ::empty()) return "invalid";
    else if (index < 0 || s <= index) return "invalid";
    else
    {
        if (index == 0) return head->data;
        else if (index == (s - 1)) return tail->data;
        else
        {
            Node* cur = head->next;
            for (int i = 1; i < (s - 1); i++)
            {
                if (index == i) return cur->data;
                cur = cur->next;
            }
        }
    }
}

string Circ::atFromTail(int index)
{
    int s = Circ::size();
    if (Circ::empty()) return "invalid";
    else if (index < 0 || s <= index) return "invalid";
    else
    {
        if (index == 0) return tail->data;
        else if (index == (s - 1)) return head->data;
        else
        {
            Node* cur = tail->prev;
            for (int i = 1; i < (s - 1); i++)
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

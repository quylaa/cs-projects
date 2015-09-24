// Written by Aleks Christensen

#ifndef CIRC_H_
#define CIRC_H_

#include <string>
#include <cstddef>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include "CircularDLLInterface.h"

class Circ : public CircularDLLInterface
{
    private:

        struct Node
        {
            // Data stored in node
            string data;
            // next node in list
            Node* next;
            // prev node in list
            Node* prev;

            Node(const string& dataItem, Node* prevPtr = NULL, Node* nextPtr = NULL) :
                data(dataItem), prev(prevPtr), next(nextPtr) {};
        };

        // top of list
        Node* head;
        // bottom of list
        Node* tail;

        /*
         * returns node at given index
         */
        Node* find(int index);

    public:

        Circ();
        ~Circ();


        void linking();
        /*
         * Returns index of given name
         * 
         * 0 if nonexistant
         */ 
        int getIndex(string name);

        /*
         * Checks if given name is in list already
         *
         * returns true if name exists, false otherwise
         */
        bool check(string name);

        /*
         * Shuffles the list
         */
        void shuffle();

        /*
         * Uses given count and size, and returns safe index 
         */
        string test(int count);

        /*
         * Runs the simulated Josephus scenario
         *
         * returns name of victor
         */
        string run(int count);

        /*
         * Adds given name to beginning such that 
         * atFromHead(0) == name and atFromTail(size() - 1) == name.
         * After, size should have increased by 1.
         *
         * returns false if name already exists, true if successful
         */
        bool insertHead(string name);

        /*
         * Adds given name to end of list such that
         * atFromHead(size() - 1) == name and atFromTail(0) == name.
         * After, size should have increased by 1.
         *
         * returns false if name already exists, true if successful
         */
        bool insertTail(string name);

        /*
         * Inserts given name into given index of list such that
         * atFromHead(index) == name. All values should shift down
         * one index to accomodate new value. After, size should have
         * increased by 1.
         *
         * return false if name already exists or index is out of range,
         * true if successful
         */
        bool insertAt(string name, int index);

        /*
         * Removes value at beginning of list. After, size() should
         * decrease by 1 and all values should shift 1 index forward.
         * If only 1 item is left, head and tail pointers should be
         * returned to a NULL state.
         *
         * returns false if attempting to remove from empty list, 
         * true if successful
         */
        bool removeHead();

        /*
         * Removes value at end of list. After, size() should decrease
         * by 1 and all index values remain unchanged. If only 1 item
         * remains, return head and tail pointers to NULL state.
         *
         * returns false if attempting to remove from empty list,
         * true if successful
         */
        bool removeTail();

        /*
         * Removes value at given index measured from beginning.
         * index 0 is beginning of list. After, size() should decrease
         * by 1 and all following index values should shift forward by 1.
         * If only 1 item remains and index 0 is given, head and tail
         * pointers should return to NULL state.
         *
         * returns false if attempting to remove from empty list or if index
         * is out of range, true if successful
         */
        bool removeAt(int index);

        /*
         * Removes all nodes from list and reset structure to empty. size()
         * should return 0 after this.
         */
        void clear();

        /*
         * Used to measure size of list.
         *
         * returns number of items in list.
         */
        int size();

        /*
         * Wrapper to check if list is empty.
         *
         * returns true if empty, false otherwise.
         */
        bool empty();

        /*
         * Measured from the head, where the beginning is indexed as 0,
         * and end is indexed as size() - 1.
         *
         * returns string located at given index, "invalid" if invalid index given
         */
        string atFromHead(int index);

        /*
         * Measured from tail, where end is indexed as 0 and beginning
         * is size() - 1.
         *
         * returns string at given index, "invalid" if invalid index given
         */
        string atFromTail(int index);
};

#endif

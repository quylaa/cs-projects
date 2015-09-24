// Written by Aleks Christensen

#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <algorithm>
#include "Circ.h"

/*
 * Operation 1
 * Import names from text file
 */
bool import(Circ* band)
{
    cin.ignore();
    string fileName;

    cout << "Please enter the location of the file: ";
    getline(cin, fileName);
    ifstream file(fileName);
    if (file)
    {
        for (string line; getline(file, line);)
        {
            line.erase(remove(line.begin(), line.end(), '\r'), line.end());
            if(band->insertTail(line)) continue;
            else 
            {
                cout << "!!-- Could not insert name. Breaking... --!!" << endl;
                return false;
            }
        }
        return true;
    }
    else
    {
        cout << "!!-- Could not open file for importing --!!" << endl;
        return false;
    }
}

/*
 * Operation 2
 * Display each name with index
 */
void display(Circ* band)
{
    int s = band->size();

    cout << "\\\\-- Josephus' Band --\\\\" << endl;
    for (int i = 0; i < s; i++)
    {
        cout << i << " - " << band->atFromHead(i) << endl;
    }
    cout << endl;
}

/*
 * Operations 3 * 4
 * Add name to roster, either prepending or appending
 */
bool add(Circ* band)
{
    cin.ignore();
    cout << "Please enter the name of the person to add: ";
    string name;
    getline(cin, name);
    cout << endl << "Now enter the index to add this person: ";
    int idx;
    cin >> idx;

    if (band->insertAt(name, idx))
    {
        cout << endl << "|-|- Person successfully added -|-|" << endl << endl;
        return true;
    }
    else
    {
        //cout << endl << "!!-- Could not add person --!!" << endl;
        return false;
    }
}

/*
 * Operation 5
 * Remove name from roster by index
 */
bool remove(Circ* band, int index)
{
    if (band->removeAt(index))
    {
        cout << "|-|- Successfully removed person -|-|" << endl << endl;
        return true;
    }
    else return false;
}

/*
 * Operation 6
 * Shuffle roster
 */
void shuffle(Circ* band)
{
    band->shuffle();
}

/*
 * Operation 7
 * Calculate safe index from given count
 */
int safe(Circ* band, int count, int size)
{
    Circ* temp = new Circ();
    // for (int t = 0; t < band->size(); t++)
    // {
    //     temp->insertHead(band->atFromHead(t));
    // }
    // string name = temp->run(count);
    // for (int i = 0; i < band->size(); i++)
    // {
    //     if (band->atFromHead(i) == name) return i;
    // }
    string str;
    for (int i = 0; i < size; i++)
    {
        (char)i;
        str = i;
        temp->insertTail(str);
    }
    return stoi(temp->test(count));
}


/*
 * Operation 8
 * Dispatch simulation
 */
bool dispatch(Circ* band, int count)
{
    string victor = band->run(count);
    cout << endl << "The Survivor: " << victor << endl;
    return true;
}

/* ------------------------------ */
/* Non-required defined functions */
/* ------------------------------ */

// Print menu and handle input
bool menu(Circ* band)
{
    char in;

    cout << "//-- Menu --//" << endl << endl;
    cout << "# [I]mport file of names     #" << endl;
    cout << "# [D]isplay band of people   #" << endl;
    cout << "# [A]dd a person to the band #" << endl;
    cout << "# [R]emove a person          #" << endl;
    cout << "# [S]huffle the band order   #" << endl;
    cout << "# [C]alculate safe position  #" << endl;
    cout << "# [E]xecute simulation       #" << endl;
    cout << "# [P]rint list               #" << endl;
    cout << "# C[l]ear list               #" << endl;
    cout << "# [Q]uit                     #" << endl;
    cout << endl << ">";
    cin >> in;
    in = tolower(in);
    cout << endl;

    if (in == 'i')
    {
        if (import(band)) return true;
        else
        {
            cout << "!!-- Could not import file --!!" << endl << endl;
            return true;
        }
    }
    else if (in == 'd')
    {
        display(band);
        return true;
    }
    else if (in == 'a')
    {
        if (add(band)) return true;
        else
        {
            cout << "!!-- Could not add person --!!" << endl << endl;
            return true;
        }
    }
    else if (in == 'r')
    {
        int idx;
        
        cout << "Please enter the index of the person to remove: ";
        cin >> idx;
        if (remove(band, idx))
        {
            cout << endl << "|-|- Person successfully removed -|-|" << endl;
            return true;
        }
        else
        {
            cout << endl << "!!-- Could not remove person --!!" << endl;
            return true;
        }
    }
    else if (in == 's')
    {
        shuffle(band);
        cout << "|-|- Band successfully shuffled -|-|" << endl;
        return true;
    }
    else if (in == 'c')
    {
        cout << "Please enter the number to count by: ";
        int cnt;
        cin >> cnt;
        cout << endl << "Now enter the desired size: ";
        int sz;
        cin >> sz;

        int idx = safe(band, cnt, sz);
        cout << "##-- Safe index: " << idx << " --##" << endl;
        cout << "##-- Initial size: " << sz << " --##" << endl;
        cout << "##-- Count amount: " << cnt << " --##" << endl;
        return true;
    }
    else if (in == 'e')
    {
        cout << "Please enter the number to count by: ";
        int cnt;
        cin >> cnt;

        if (dispatch(band, cnt)) return true;
    }
    else if (in == 'l')
    {
        band->clear();
        return true;
    }
    else if (in == 'q')
    {
        return false;
    }
    else if (in == 'p')
    {
        band->linking();
        return true;
    }
    else {
        cout << "!!-- Could not interpret input --!!" << endl;
        return true;
    }
}



/* ---- */
/* Main */
/* ---- */

int main()
{
    Circ* band = new Circ();
    
    cout << "-- Josephus Problem Simulator --" << endl << endl;

    while (true)
    {
        if (!menu(band)) break;
    }
    return 0;
}


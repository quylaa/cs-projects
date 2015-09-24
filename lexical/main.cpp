// Written by Aleks Christensen

// #include <vector>
#include <iostream>
#include "fsmbox.h"

string getInput(string fileName)
{
    stringstream iput;
    ifstream file(fileName);
    if (file) {
        for (string line; getline(file, line);) {
            iput << line << endl;
        }
    }
    return iput.str();
}

string tokenize(string lines)
{
    FSMBox fsm;
    string tokenstring = fsm.tokens(lines);
    return tokenstring;
}

int main()
{
    string fileName;
    cin >> fileName;
    string lines = getInput(fileName);
    if (lines.empty()) return -1;
    else cout << tokenize(lines);
    return 0;
}

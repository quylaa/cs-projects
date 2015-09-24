// Written by Aleks Christensen

// #include <vector>
#include <iostream>
#include "fsmbox.h"

stringstream getInput(string fileName)
{
    stringstream iput;
    ifstream file(fileName);
    if (file) {
        for (string line; getline(file, line);) {
            iput << line << endl;
        }
    }
    return iput;
}

string tokenize(stringstream lines)
{
    FSMBox fsm;
    // for (size_t i = 0; i < lines.size(); i++) {
    stringstream tokenstring = fsm.tokens(lines);
    // }
    return tokenstring.str();
}

int main()
{
    cin >> string fileName;
    stringstream lines = getInput(fileName);
    if (lines.rdbuf()->in_avail() == 0) return -1;
    else cout << tokenize(lines) << endl;
    return 0;
}

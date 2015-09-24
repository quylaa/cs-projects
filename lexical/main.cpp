// Written by Aleks Christensen

#include <vector>
#include <iostream>
#include "fsmbox.h"

vector<string> getInput(string fileName)
{
    vector<string> lines;
    ifstream file(fileName);
    if (file) {
        for (string line; getline(file, line);) {
            lines.push_back(line);
        }
    }
    return lines;
}

string tokenize(vector<string> lines)
{
    FSMBox fsm;
    stringstream out;
    for (size_t i = 0; i < lines.size(); i++) {
        out << fsm.tokens(lines.at(i), 2);
    }
    return out.str();
}

int main()
{
  return 0;
}

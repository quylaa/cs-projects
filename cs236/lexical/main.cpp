// Written by Aleks Christensen

#include <iostream>
#include "fsmbox.h"

stack<char> getInput(string fileName)
{
    stack<char> iput;
    ifstream file(fileName);
    if (file) {
        char t;
        while (!file.eof()) {
            file.get(t);
            iput.push(t);
        }
    }
    iput.pop();
    iput.push('\000');
    file.close();
    return iput;
}

stack<char> flip(stack<char> iput)
{
    stack<char> lines;
    while (!iput.empty()) {
        lines.push(iput.top());
        iput.pop();
    }
    return lines;
}

string tokenize(stack<char> lines)
{
    FSMBox fsm;
    string tokenstring = fsm.tokens(lines);
    return tokenstring;
}

int main(int argc, char* argv[])
{
    stack<char> lines = flip(getInput(argv[1]));
    cout << tokenize(lines);
    return 0;
}

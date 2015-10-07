// Written by Aleks Christensen

#include <fstream>
#include <iostream>
#include "fsmbox.h"

using namespace std;

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

vector<Token> tokenize(stack<char> lines)
{
    FSMBox fsm;
    string tokenstring = fsm.tokens(lines);
    return tokenstring;
}

string toString(Token t)
{
    string s;
    s.push_back("(");
    s.push_back(t.content);
    s.push_back(",");
    s.push_back(t.type);
    s.push_back(",");
    s.push_back(t.line);
    s.push_back(")");
    return s;
}

int main(int argc, char* argv[])
{
    stack<char> lines = flip(getInput(argv[1]));
    vector<Token> tokens = tokenize(lines);
    for (size_t l = 0; l < tokens.size(); ++l) {
        cout << toString(tokens.at(l)) << endl;
    }
    return 0;
}

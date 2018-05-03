// Written by Aleks Christensen

#include <fstream>
#include <iostream>
#include "fsmbox.h"
#include "datalogProgram.h"

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
    vector<Token> tokenlist = fsm.tokens(lines);
    return tokenlist;
}

string datalog(vector<Token> tokens)
{
    datalogProgram dlp;
    return dlp.parse(tokens);
}

string toString(Token t)
{
    string s;
    s.append("(\"");
    s.append(t.content);
    s.append("\",");
    s.append(t.type);
    s.push_back(',');
    s.append(to_string(t.line));
    s.push_back(')');
    return s;
}

int main(int argc, char* argv[])
{
    stack<char> lines = flip(getInput(argv[1]));
    // vector<Token> tokens = tokenize(lines);
    cout << datalog(tokenize(lines));
    // for (size_t t = 0; t < tokens.size(); ++t) {
    //     cout << toString(tokens.at(t)) << endl;
    // }
    return 0;
}

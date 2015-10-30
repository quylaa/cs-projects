// Written by Aleks Christensen

#include <fstream>
#include <iostream>
#include <sstream>
#include "fsmbox.h"
#include "datalogProgram.h"
#include "database.h"
#include "handler.h"

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

vector< vector<Predicate> > datalog(vector<Token> tokens)
{
    datalogProgram dlp;
    return dlp.parse(tokens);
}

// Database makedata(vector< vector<Predicate> > datas)
// {
//     Handler h;
//     return h.makeData(datas);
// }

int main(int argc, char* argv[])
{
    stack<char> lines = flip(getInput(argv[1]));
    vector< vector<Predicate> > datas = datalog(tokenize(lines));
    Handler h;
    Database db = h.makeData(datas);
    // vector<Relation> results = h.doQueries()
    cout << db.print() << endl;
    // cout << database(datas) << endl;
    return 0;
}

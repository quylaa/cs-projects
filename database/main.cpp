// Written by Aleks Christensen

#include <fstream>
#include <iostream>
#include <sstream>
#include "fsmbox.h"
#include "datalogProgram.h"
#include "relation.h"

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

// string database(vector< vector<Predicate> > datas)
// {
//     Database db;
//     return db.make(datas);
// }

string makedata(vector< vector<Predicate> > datas)
{
    vector<Predicate> schemes = datas.at(0);
    vector<Predicate> facts = datas.at(1);
    vector<Predicate> queries = datas.at(2);

    vector<Relation> relations;

    for (vector<Predicate>::iterator st = schemes.begin(); st != schemes.end(); ++st) {
        string name = st->id;
        vector<Param> parms = st->params;
        vector<string> schema;
        for (size_t i = 0; i < parms.size(); ++i) {
            /*if (parms.at(i).isString == true)*/ schema.push_back(parms.at(i).toString());
        }
        relations.push_back(Relation(name, schema));
    }

    for (vector<Predicate>::iterator pt = facts.begin(); pt != facts.end(); ++pt) {
        for (size_t j = 0; j < relations.size(); ++j) {
            if (pt->id == relations.at(j).getName()) {
                vector<Param> parms = pt->params;
                vector<string> tups;
                for (size_t t = 0; t < parms.size(); ++t) {
                    if (parms.at(t).isString) tups.push_back(parms.at(t).toString());
                }
                relations.at(j).addTuple(tups);
            }
        }
    }
    ostringstream out;
    for (vector<Relation>::iterator rt = relations.begin(); rt != relations.end(); ++rt) {
        out << rt->print();
    }
    return out.str();
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
    vector< vector<Predicate> > datas = datalog(tokenize(lines));
    cout << makedata(datas) << endl;
    // cout << database(datas) << endl;
    return 0;
}

// Written by Aleks Christensen

#ifndef RELATION_H_
#define RELATION_H_

#include <utility>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <sstream>
#include <iostream>
#include <algorithm>
#include "predicate.h"

using namespace std;

class Relation
{
    private:
        string name;
        vector<string> schema;
        set< vector<string> > datas;

    public:

        Relation(string n, vector<string> s) : name(n), schema(s) {};
        Relation(string n, vector<string> s, set< vector<string> > d) : name(n), schema(s), datas(d) {};
        ~Relation() {};

        void addTuple(vector<string> more);

        Relation Select(vector<Param> items);

        Relation Project(vector<Param> items);

        Relation Project(vector<string> items);

        void Rename(vector<string> ids);

        string makeString();

        string print();

        string getName();

        int getSize();

        set< vector<string> > getDatas();

        vector<string> getSchema();

        string dprint();
};

#endif

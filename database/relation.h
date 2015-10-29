// Written by Aleks Christensen

#ifndef RELATION_H_
#define RELATION_H_

#include <utility>
#include <string>
#include <vector>
#include <set>

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

        set< vector<string> > Select(vector< pair<string, string> > items);

        set< vector<string> > Project(vector< pair<string, string> > items);

        // set< vector<string> > Rename(vector<string> from, vector<string> to);

        string print();

        string getName();

        vector<string> getSchema();
};

#endif

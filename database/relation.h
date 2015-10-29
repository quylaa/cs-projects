// Written by Aleks Christensen

#ifndef RELATION_H_
#define RELATION_H_

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
        ~Relation() {};

        void addTuple(vector<string> more);

        set< vector<string> > Select(vector<string> items);

        // set< vector<string> > Project(vector<string> items);
        //
        // set< vector<string> > Rename(vector<string> from, vector<string> to);

        string print();

        string getName();
};

#endif

// Written by Aleks Christensen

#ifndef RELATION_H_
#define RELATION_H_

#include <utility>
#include <string>
#include <vector>
#include <set>
#include <map>

using namespace std;

class Relation
{
    private:
        string name;
        vector<string> schema;
        set< vector<string> > datas;

        // bool hasSelected = false;
        // bool hasProjected = false;
        bool Renamed = false;

    public:

        Relation(string n, vector<string> s) : name(n), schema(s) {};
        Relation(string n, vector<string> s, set< vector<string> > d) : name(n), schema(s), datas(d) {};
        // Relation(string n, vector<string> s, set< vector<string> > d, vector<bool> hd)
            // : name(n), schema(s), datas(d), hasSelected(hd[0]), hasProjected(hd[1]), hasRenamed(hd[2]) {};
        ~Relation() {};

        void addTuple(vector<string> more);

        Relation Select(vector< pair<string, string> > items);

        Relation Project(vector< pair<string, string> > items);

        void Rename(vector<string> ids);

        string makeString();

        string print();

        string getName();

        set< vector<string> > getData();

        vector<string> getSchema();

        bool hasRenamed();
};

#endif

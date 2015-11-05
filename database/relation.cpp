// Written by Aleks Christensen

#include <sstream>
#include <iostream>
#include "relation.h"

void Relation::addTuple(vector<string> more)
{
    datas.insert(more);
}

set< vector<string> > Relation::Select(vector< pair<string, string> > items)
{
    cout << "DOING SELECT" << endl;
    set< vector<string> > results;
    vector<string> params;
    for (size_t it = 0; it < items.size(); ++it) {
        items.at(it).second == "STR" ? params.push_back(items.at(it).first)
            : params.push_back("WRONG");
        // string type = items.at(it).second;
        // int which = 0;
        // for (size_t s = 0; s < schema.size(); ++s) { if (schema.at(s) == col) which = s; }
    }
    bool matches = true;
    for (set< vector<string> >::iterator rt = datas.begin(); rt != datas.end(); ++rt) {
        matches = true;
        for (size_t i = 0; i < params.size(); ++i) {
            if (params.at(i) == "WRONG") continue;
            if (rt->at(i) != params.at(i)) matches = false;
            cout << rt->at(i) << " ";
        }
        cout << endl;
        if (matches == true/*rt->at(i) == val*/) results.insert((*rt));
        for (size_t j = 0; j < (*rt).size(); ++j) {
            cout << (*rt).at(j) << " ";
        }
    }
    cout << endl;
    return results;
}

map<string, vector<string> > Relation::Project(vector< pair<string, string> > items)
{
    cout << "DOING PROJECT\n";
    map<string, vector<string> > results;

    for (set< vector<string> >::iterator rt = datas.begin(); rt != datas.end(); ++rt) {
        for (size_t it = 0; it < items.size(); ++it) {
            if (items.at(it).second != "ID") continue;
            string val = rt->at(it);
            cout << schema.at(it) << " -> " << val << " ";
            try {
                results.at(schema.at(it)).push_back(val);
            } catch (const out_of_range& oor) {
                vector<string> temp = {val};
                results.insert(pair<string, vector<string> >(schema.at(it), temp));
            }
        }

    }
    cout << endl;
    return results;
}
//
// set< vector<string> > Relation::Rename(vector<string> from, vector<string> to)
// {
//     return new set< vector<string> >;
// }

string Relation::print()
{
    ostringstream out;
    // out << "**" << name << "**" << endl;
    //for (vector<string>::iterator vt = schema.begin(); vt != schema.end(); ++vt) {
        //out << " " << (*vt) << "  ";
    //}
    //out << "\n-------\n";
    int k = 0;
    int t = 0;
    for (set< vector<string> >::iterator st = datas.begin(); st != datas.end(); ++st) {
        if (k != 0) k++;
        for (size_t s = 0; s < st->size(); ++s) {
            t++;
            out << schema.at(k) << "=" << st->at(s) << endl;
            //if (s != (st->size()-1)) out << " ";
        }
        //out << endl;
    }
    out << endl;
    ostringstream o;
    o << "(" << t << ")\n" << out.str();
    return o.str();
}

string Relation::getName()
{
    return name;
}

vector<string> Relation::getSchema()
{
    return schema;
}

set <vector<string> > Relation::getData()
{
    return datas;
}

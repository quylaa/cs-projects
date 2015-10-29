// Written by Aleks Christensen

#include <sstream>
#include "relation.h"

void Relation::addTuple(vector<string> more)
{
    datas.insert(more);
}

set< vector<string> > Relation::Select(vector< pair<string, string> > items)
{
    set< vector<string> > results;
    vector<string> params;
    for (size_t it = 0; it < items.size(); ++it) {
        params.push_back(items.at(it).first);
        // string type = items.at(it).second;
        // int which = 0;
        // for (size_t s = 0; s < schema.size(); ++s) { if (schema.at(s) == col) which = s; }
    }
    bool matches = true;
    for (set< vector<string> >::iterator rt = datas.begin(); rt != datas.end(); ++rt) {
        matches = true;
        for (size_t i = 0; i < params.size(); ++i) {
            if(params.at(i) != "STR") continue;
            if (rt->at(i) != params.at(i)) matches = false;
        }
        if (matches == true/*rt->at(i) == val*/) results.insert((*rt));
    }
    return results;
}

set< vector<string> > Relation::Project(vector< pair<string, string> > items)
{
    set< vector<string> > results;
    for (size_t it = 0; it < items.size(); ++it) {
        string val = items
    }

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
    out << "**" << name << "**" << endl;
    for (vector<string>::iterator vt = schema.begin(); vt != schema.end(); ++vt) {
        out << " " << (*vt) << "  ";
    }
    out << "\n-------\n";

    for (set< vector<string> >::iterator st = datas.begin(); st != datas.end(); ++st) {
        for (size_t s = 0; s < st->size(); ++s) {
            out << st->at(s);
            if (s != (st->size()-1)) out << " ";
        }
        out << endl;
    }
    out << endl;
    return out.str();
}

string Relation::getName()
{
    return name;
}

vector<string> Relation::getSchema()
{
    return schema;
}

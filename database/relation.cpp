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
    for (vector< pair<string, string> >::iterator it = items.begin(); it != items.end(); ++it) {
        string col = it->first;
        string val = it->second;
        int which = 0;
        for (size_t s = 0; s < schema.size(); ++s) { if (schema.at(s) == col) which = s; }
        for (set< vector<string> >::iterator rt = datas.begin(); rt != datas.end(); ++rt) {
            if (rt->at(which) == val) results.insert((*rt));
        }
    }
    return results;
}

// set< vector<string> > Relation::Project(vector<string> items)
// {
//     return new set< vector<string> >;
// }
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

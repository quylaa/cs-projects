// Written by Aleks Christensen

#include <sstream>
#include "relation.h"

void Relation::addTuple(vector<string> more)
{
    datas.insert(more);
}

set< vector<string> > Relation::Select(vector<string> items)
{
    set< vector<string> > results;
    
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

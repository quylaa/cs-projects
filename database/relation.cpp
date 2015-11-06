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
    hasSelected = true;
    set< vector<string> > results;
    vector<string> params;
    for (size_t it = 0; it < items.size(); ++it) {
        items.at(it).second == "STR" ? params.push_back(items.at(it).first)
            : params.push_back("WRONG");
    }
    bool matches = true;
    for (set< vector<string> >::iterator rt = datas.begin(); rt != datas.end(); ++rt) {
        matches = true;
        for (size_t i = 0; i < params.size(); ++i) {
            if (params.at(i) == "WRONG") continue;
            if (rt->at(i) != params.at(i)) matches = false;
        }
        if (matches == true/*rt->at(i) == val*/) results.insert((*rt));
    }
    return results;
}

map<string, vector<string> > Relation::Project(vector< pair<string, string> > items)
{
    hasProjected = true;
    map<string, vector<string> > results;
    for (set< vector<string> >::iterator rt = datas.begin(); rt != datas.end(); ++rt) {
        for (size_t it = 0; it < items.size(); ++it) {
            if (items.at(it).second != "ID") continue;
            string val = rt->at(it);
            try {
                results.at(schema.at(it)).push_back(val);
            } catch (const out_of_range& oor) {
                vector<string> temp = {val};
                results.insert(pair<string, vector<string> >(schema.at(it), temp));
            }
        }
    }
    return results;
}

void Relation::Rename(string from, string to)
{
    hasRenamed = true;
    for (size_t i = 0; i < schema.size(); ++i) {
        if (schema.at(i) == from) {
            schema.at(i) = to;
            for (size_t j = 0; j < i; ++j) {
                if (schema.at(j) == schema.at(i)) {
                    set< vector<string> > newDatas;
                    for (set< vector<string> >::iterator st = datas.begin(); st != datas.end(); ++st) {
                        if (st->at(i) == st->at(j)) newDatas.insert((*st));
                    }
                    datas = newDatas;
                }
            }
        }
    }
}

string Relation::makeString()
{
    ostringstream out;
    for (set< vector<string> >::iterator st = datas.begin(); st != datas.end(); ++st) {
        out << "  ";
        vector<string> dn;
        for (size_t s = 0; s < st->size(); ++s) {
            bool fnd = false;
            for (size_t i = 0; i < dn.size(); ++i) {
                if (dn.at(i) == schema.at(s)) fnd = true;
            }
            if (fnd) continue;
            out << schema.at(s) << "=" << st->at(s);
            // if (s != (st->size()-1))
            dn.push_back(schema.at(s));
        }
        out << endl;
    }
    return out.str();
}

string Relation::print()
{
    ostringstream out;
    bool dupe = false;
    for (size_t i = 0; i < schema.size(); ++i) {
        if (i == 0) continue;
        if (schema.at(i) == schema.at(i-1)) {
            dupe = true;
        }
    }
    if (dupe) out << makeString();
    else {
        for (set< vector<string> >::iterator st = datas.begin(); st != datas.end(); ++st) {
            out << "  ";
            for (size_t s = 0; s < st->size(); ++s) {
                out << schema.at(s) << "=" << st->at(s);
                if (s != (st->size()-1)) out << ", ";
            }
            out << endl;
        }
    }
    ostringstream o;
    o << "(" << datas.size() << ")\n" << out.str();
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

vector<bool> Relation::hasDone()
{
    vector<bool> done;
    done.push_back(hasSelected);
    done.push_back(hasProjected);
    done.push_back(hasRenamed);
    return done;
}

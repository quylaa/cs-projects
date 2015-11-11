// Written by Aleks Christensen

#include <sstream>
#include <iostream>
#include "relation.h"

void Relation::addTuple(vector<string> more)
{
    datas.insert(more);
}

Relation Relation::Select(vector< pair<string, string> > items)
{
    // cout << "DOING SELECT" << endl;
    // hasSelected = true;
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
            // cout << rt->at(i) << " \n";
        }
        if (matches == true/*rt->at(i) == val*/) results.insert((*rt));
    }
    Relation temp(name, schema, results);
    return temp;
}

Relation Relation::Project(vector< pair<string, string> > items)
{
    // cout << "DOING PROJECT" << endl;
    // hasProjected = true;
    set< vector<string> > results;
    vector<string> newSchema;
    vector<int> indexes;
    for (size_t t = 0; t < items.size(); ++t) {
        if (items.at(t).second == "ID") {
            indexes.push_back(t);
            newSchema.push_back(schema.at(t));
        }
    }
    for (set< vector<string> >::iterator rt = datas.begin(); rt != datas.end(); ++rt) {
        vector<string> newtup;
        for (size_t it = 0; it < indexes.size(); ++it) {
            // if (items.at(it).second != "ID") continue;
            newtup.push_back(rt->at(it));
            // cout << schema.at(it) << " -> " << val << " \n";
            // try {
            //     results.at(schema.at(it)).push_back(val);
            // } catch (const out_of_range& oor) {
            //     vector<string> temp = {val};
            //     results.insert(pair<string, vector<string> >(schema.at(it), temp));
            // }
        }
        results.insert(newtup);
    }

    // set< vector<string> > dat;
    // int l;

    // for (map<string, vector<string> >::iterator vt = results.begin(); vt != results.end(); ++vt) {
    //     newSchema.push_back(vt->first);
    //     l = vt->second.size();
    // }
    // for (int m = 0; m < l; ++m) {
    //     vector<string> newt;
    //     for (map<string, vector<string> >::iterator vt = results.begin(); vt != results.end(); ++vt) {
    //             newt.push_back(vt->second.at(m));
    //     }
    //     dat.insert(newt);
    // }
    Relation temp(name, newSchema, results);
    return temp;
}

void Relation::Rename(vector<string> ids)
{
    // cout << "DOING RENAME" << endl;
    // hasRenamed = true;
    // if (schema.size() == 1) {
    //     cout << schema.at(0) << " => " << ids.at(0).second << " \n";
    //     schema.at(0) = ids.at(0).second;
    // }
    // else {
        for (size_t pt = 0; pt < schema.size(); ++pt) {
            // cout << schema.at(pt) << " => " << ids.at(pt) << " \n";
            schema.at(pt) = ids.at(pt);
        }
        for (size_t i = 0; i < schema.size(); ++i) {
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
    // }
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
            if (s != (st->size()-1)) out << ", ";
            dn.push_back(schema.at(s));
        }
        out << endl;
    }
    string o = out.str();
    if (o.at(o.size()-3) == ',') {
        o = o.substr(0, o.size()-3);
        o.push_back('\n');
    }
    return o;
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
    // ostringstream o;
    // o << "(" << datas.size() << ")\n" << out.str();
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

set <vector<string> > Relation::getData()
{
    return datas;
}

// vector<bool> Relation::hasDone()
// {
//     vector<bool> done;
//     done.push_back(hasSelected);
//     done.push_back(hasProjected);
//     done.push_back(hasRenamed);
//     return done;
// }

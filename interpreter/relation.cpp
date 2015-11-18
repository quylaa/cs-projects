// Written by Aleks Christensen

#include "relation.h"

void Relation::addTuple(vector<string> more)
{
    datas.insert(more);
}

Relation Relation::Select(vector< pair<string, string> > items)
{
    set< vector<string> > results;
    vector<string> params;
    for (size_t it = 0; it < items.size(); ++it) {
        items.at(it).second == "STR" ? params.push_back(items.at(it).first)
            : params.push_back("WRONG");
    }
    bool matches = true;
    // for (set< vector<string> >::iterator rt = datas.begin(); rt != datas.end(); ++rt) {
    for (auto rt : datas) {
        matches = true;
        for (size_t i = 0; i < params.size(); ++i) {
            if (params.at(i) == "WRONG") continue;
            if (rt.at(i) != params.at(i)) matches = false;
        }
        if (matches == true) results.insert(rt);
    }
    Relation temp(name, schema, results);
    return temp;
}

Relation Relation::Project(vector< pair<string, string> > items)
{
    set< vector<string> > results;
    vector<string> newSchema;
    vector<int> indexes;
    for (size_t t = 0; t < items.size(); ++t) {
        if (items.at(t).second == "ID") {
            indexes.push_back(t);
            newSchema.push_back(schema.at(t));
        }
    }
    // for (set< vector<string> >::iterator rt = datas.begin(); rt != datas.end(); ++rt) {
    for (auto rt : datas) {
        vector<string> newtup;
        for (size_t it = 0; it < indexes.size(); ++it) {
            newtup.push_back(rt.at(indexes.at(it)));
        }
        results.insert(newtup);
    }

    Relation temp(name, newSchema, results);
    return temp;
}

void Relation::Rename(vector<string> ids)
{
        for (size_t pt = 0; pt < schema.size(); ++pt) {
            schema.at(pt) = ids.at(pt);
        }
        for (size_t i = 0; i < schema.size(); ++i) {
            for (size_t j = 0; j < i; ++j) {
                if (schema.at(j) == schema.at(i)) {
                    set< vector<string> > newDatas;
                    // for (set< vector<string> >::iterator st = datas.begin(); st != datas.end(); ++st) {
                    for (auto st : datas) {
                        if (st.at(i) == st.at(j)) newDatas.insert(st);
                    }
                    datas = newDatas;
                }
            }
        }
}

string Relation::makeString()
{
    ostringstream out;
    // for (set< vector<string> >::iterator st = datas.begin(); st != datas.end(); ++st) {
    for (auto st : datas) {
        out << "  ";
        vector<string> dn;
        for (size_t s = 0; s < st.size(); ++s) {
            bool fnd = false;
            for (size_t i = 0; i < dn.size(); ++i) {
                if (dn.at(i) == schema.at(s)) fnd = true;
            }
            if (fnd) continue;
            if (s != 0) out << ", ";
            out << schema.at(s) << "=" << st.at(s);
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
    vector<string> tschema = schema;
    sort(tschema.begin(), tschema.end());
    for (size_t i = 0; i < tschema.size(); ++i) {
        if (i == 0) continue;
        if (tschema.at(i) == tschema.at(i-1)) {
            dupe = true;
        }
    }
    if (dupe) out << makeString();
    else {
        // for (set< vector<string> >::iterator st = datas.begin(); st != datas.end(); ++st) {
        for (auto st : datas) {
            out << "  ";
            for (size_t s = 0; s < st.size(); ++s) {
                if (s != 0) out << ", ";
                out << schema.at(s) << "=" << st.at(s);
            }
            out << endl;
        }
    }
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

int Relation::getSize()
{
    return datas.size();
}

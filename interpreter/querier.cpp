// Written by Aleks Christensen

#include "querier.h"

void Querier::makeData(vector<Token> tokens)
{
    datalogProgram dlp;
    if (dlp.parse(tokens)) {
        Database db;
        vector<Predicate> schemes = dlp.getSchemes();
        vector<Predicate> facts = dlp.getFacts();
        vector<Rule> rules = dlp.getRules();
        vector<Predicate> queries = dlp.getQueries();
        vector<Relation> relations;

        getSchemes(schemes, relations);
        getFacts(facts, relations);

        for (auto rt : relations) {
            db.addRelation(rt);
        }
        doRules(rules, db);
        doQueries(queries, db);
    }
};

void Querier::getSchemes(vector<Predicate> schemes, vector<Relation> &relations)
{
    for (auto st : schemes) {
        string name = st.id;
        vector<Param> parms = st.params;
        vector<string> schema;
        for (size_t i = 0; i < parms.size(); ++i) {
            schema.push_back(parms.at(i).toString());
        }
        relations.push_back(Relation(name, schema));
    }
};

void Querier::getFacts(vector<Predicate> facts, vector<Relation> &relations)
{
    for (auto pt : facts) {
        for (size_t j = 0; j < relations.size(); ++j) {
            if (pt.id == relations.at(j).getName()) {
                vector<Param> parms = pt.params;
                vector<string> tups;
                for (size_t t = 0; t < parms.size(); ++t) {
                    if (parms.at(t).isString) tups.push_back(parms.at(t).toString());
                }
                relations.at(j).addTuple(tups);
            }
        }
    }
};

void Querier::doRules(vector<Rule> rules, Database &db)
{
    for (auto rt : rules) {
        Predicate head = rt.head;
        vector<Predicate> right = rt.rules;
        vector<Relation> rels;

        for (auto pred : right) rels.push_back(doQuery(pred, db));
        // for (auto r : rels) cout << r.getName() << " " << r.print() << endl;
        // rels.size() > 1 ? Relation result = join(rels) : Relation result = rels.at(0);
        join(rels);
    }
}

Relation Querier::join(vector<Relation> &rels)
{
    while (rels.size() > 1)
    {
        vector< pair<int,int> > dupes;
        set< vector<string> > datA = rels.at(0).getDatas();
        set< vector<string> > datB = rels.at(1).getDatas();
        // for (size_t i = 0; i < rels.size(); ++i) {
            // if (i+1 != rels.size()) {
                vector<string> schA = rels.at(0).getSchema();
                vector<string> schB = rels.at(1).getSchema();
                for (size_t j = 0; j < schA.size(); ++j) {
                    auto f = find(schB.begin(), schB.end(), schA.at(j));
                    if (f != schB.end()) dupes.push_back(pair<int,int>(j,f-schB.begin()));
                }
            // }
        // }
        if (!dupes.empty()) {
            set< vector<string> > newDatas;
            vector<string> newSchema = schA;
            for (auto p : dupes) {
                schB.erase(schB.begin() + p.second);
                for (auto tupA : datA) {
                    for (auto tupB : datB) {
                        if (tupA.at(p.first) == tupB.at(p.second)) {
                            tupB.erase(tupB.begin() + p.second);
                            vector<string> newTup = tupA;
                            newTup.insert(newTup.end(), tupB.begin(), tupB.end());
                            newDatas.insert(newTup);
                        }
                    }
                }
            }
            string newName = rels.at(0).getName() + rels.at(1).getName();
            newSchema.insert(newSchema.end(), schB.begin(), schB.end());
            rels.at(0) = Relation(newName, newSchema, newDatas);
            rels.erase(rels.begin()+1);
        } else {
            rels.at(0) = cProduct(rels);
            rels.erase(rels.begin()+1);
        }
        cout << rels.at(0).print() << endl;
    }
    return rels.at(0);
    // Relation crossed = cProduct(rels);
    // return natJoin(crossed);
    // map<string, bool> done;
    // bool need = false;
    // for (auto s : crossed.getSchema()) {
    //     if (done.find(s) != done.end()) {
    //         need = true;
    //         done.at(s) = true;
    //     }
    //     else done.insert(pair<string, bool>(s,false));
    // }
    // for (auto r : rels) {
    //     for (auto s : r.getSchema()) {
    //         if (done.find(s) != done.end()) {
    //             need = true;
    //             done.at(s) = true;
    //         }
    //     }
    // }
    // if (need) {
    //     vector<Relation> toJoin;
    //     vector<string> indexes;
    //     vector<Param> parms;
    //     for (auto id : done) {
    //         if (id.second) indexes.push_back(id.first);
    //     }
    //     for (auto rel : rels) {
    //         for (auto idx : indexes) {
    //             // toJoin.push_back()
    //         }
    //     }
    // }
}

Relation Querier::natJoin(Relation rel)
{
    map<string, vector<int> > indexes; // map of all duplicate schema value locations
    vector<string> sch = rel.getSchema();
    for (vector<string>::iterator idx = sch.begin(); idx != sch.end(); ++idx) {
        if (indexes.find((*idx)) != indexes.end()) continue; // if already searched for, skip
        vector<int> locs; // else initialize temp vector
        locs.push_back(idx-sch.begin()); // add current location
        do {
            vector<string>::iterator f = find(f+1, sch.end(), (*idx)); // find next dupe
            if (f != sch.end()) locs.push_back(f-sch.begin()); // if exists, add
            else break; // else break
        } while (true); // continue while there might still be duplicates
        indexes.insert(pair<string, vector<int> >((*idx), locs)); // save to map
    }
    for (auto i : indexes) { // debugging output
        cout << i.first << " :: ";
        for (auto j : i.second) {
            cout << j << " ";
        }
        cout << endl;
    }

    for (auto tup : rel.getDatas()) {
        for (auto col : indexes) {

        }
    }
    return rel;
}

Relation Querier::cProduct(vector<Relation> rels)
{
    vector<string> newSchema;
    set< vector<string> > newDatas;
    string newName;
    int tupleCnt = 1; // tracks final # tuples by multiplying each relation size together
    for (auto rel : rels) {
        for (auto s : rel.getSchema()) {
            newSchema.push_back(s); // create giant, messy schema
        }
        tupleCnt = tupleCnt * rel.getSize(); // multiply existing count by size
        newName.append(rel.getName());
    }
    for (int i = 0; i < tupleCnt; ++i) {
        vector<string> newTup;
        for (auto rel : rels) { // iterate over each relation
            for (auto tup : rel.getDatas()) { // iterate over tuples in relation
                for (auto d : tup) { // iterate over data value in tuple
                    newTup.push_back(d);
                }
            }
        }
        newDatas.insert(newTup); // add messy tuple to new set
    }
    return Relation(newName, newSchema, newDatas); // return cross product
}

void Querier::doQueries(vector<Predicate> queries, Database &db)
{
    for (size_t o = 0; o < queries.size(); ++o) {
        cout << queries.at(o).toString() << "?";
        Relation t = doQuery(queries.at(o), db);
    }
};

Relation Querier::doQuery(Predicate query, Database &db)
{
    string id = query.id;
    vector<Param> params = query.params;

    Relation r = db.getRelation(id);
    if (r.getName() == "NULL") return r;

    Relation result = r.Select(params);
    vector<string> ids;
    for (size_t r = 0; r < query.params.size(); ++r) {
        if (query.params.at(r).isID) {
            ids.push_back(query.params.at(r).value);
        }
    }
    if (!ids.empty()) {
        Relation temp = result.Project(params);
        temp.Rename(ids);
        // printResult(temp, result);
        return temp;
    }
    // printResult(result);
    return result;
};

void Querier::printResult(Relation result)
{
    if (result.getSize() == 0) {
        cout << " No\n";
    } else if (result.getSize() == 1) {
        cout << " Yes(1)\n";
    } else {
        cout << " Yes(" << result.getSize() << ")\n";
        cout << result.print();
    }
};

void Querier::printResult(Relation result, Relation prev)
{
    if (result.getSize() == 0) {
        cout << " No\n";
    } else if (!schemaComp(result, prev) || result.getSize() > 1) {
        cout << " Yes(" << result.getSize() << ")\n";
        cout << result.print();
    } else {
        cout << " Yes(1)\n";
    }
};

bool Querier::schemaComp(Relation A, Relation B)
{
    vector<string> schA = A.getSchema();
    vector<string> schB = B.getSchema();
    vector<string> isect(5);
    vector<string>::iterator it;

    it = set_intersection(schA.begin(), schA.end(), schB.begin(), schB.end(), isect.begin());
    isect.resize(it-isect.begin());
    bool emp;
    isect.empty() ? emp = false : emp = true;
    return emp;
}

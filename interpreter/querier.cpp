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

void Querier::doRules(vector<Rule> rules, Database db)
{
    for (auto rt : rules) {
        Predicate head = rt.head;
        vector<Predicate> right = rt.rules;
        vector<Relation> rels;

        for (auto pred : right) rels.push_back(doQuery(pred, db));
        for (auto r : rels) cout << r.getName() << " " << r.print() << endl;
        // rels.size() > 1 ? Relation result = join(rels) : Relation result = rels.at(0);

    }
}

Relation Querier::join(vector<Relation> rels)
{
    map<string, bool> done;
    bool need = false;
    for (auto r : rels) {
        for (auto s : r.getSchema()) {
            if (done.find(s) != done.end()) {
                need = true;
                done.at(s) = true;
            }
            else done.insert(pair<string, bool>(s,false));
        }
    }
    if (need) {
        vector<Relation> toJoin;
        vector<string> indexes;
        for (auto id : done) {
            if (id.second) indexes.push_back(id.first);
        }
        for (auto rel : rels) {
            for (auto idx : indexes) {
                // toJoin.push_back()
            }
        }
    }
}

void Querier::doQueries(vector<Predicate> queries, Database db)
{
    for (size_t o = 0; o < queries.size(); ++o) {
        cout << queries.at(o).toString() << "?";
        Relation t = doQuery(queries.at(o), db);
    }
};

Relation Querier::doQuery(Predicate query, Database db)
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

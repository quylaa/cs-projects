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
    int relcnt; // old tuple count
    int newcnt; // new tuple count
    Depend d;
    vector<SCC> order =  d.optimize(rules); // get all SCCs
    vector<int> evalCnt (order.size(), 0); // tracks how many times each SCC is evaluated
    for (size_t s = 0; s < order.size(); ++s) {
        if (order.at(s).trivial) {
            ruleLoop(rules.at((*order.at(s).scc.begin())), db);
            evalCnt.at(s)++;
        } else {
            do {
                relcnt  = db.size(); // save initial database size
                for (auto r : order.at(s).scc) {
                    ruleLoop(rules.at(r), db);
                }
                newcnt = db.size(); // get new database size
                evalCnt.at(s)++;
            } while (newcnt > relcnt); // continue until db doesnt change
        }
    }
    cout << "Rule Evaluation\n";
    for (size_t i = 0; i < order.size(); ++i) {
        cout << evalCnt.at(i) << " passes: ";
        for (auto r : order.at(i).scc) {
            cout << "R" << r;
            if (r != (*--order.at(i).scc.end())) cout << ",";
        }
        cout << endl;
    }
    cout << endl << "Query Evaluation\n";
}

bool Querier::trivial(int ruleNum, set<int> scc)
{
    for (auto s : scc) {
        if (ruleNum == s) return false;
    }
    return true;
}

void Querier::ruleLoop(Rule rule, Database &db)
{
    Predicate head = rule.head;
    vector<Predicate> right = rule.rules;
    vector<Relation> rels;
    vector<string> headVals;

    for (auto hp : head.params) headVals.push_back(hp.value);

    for (auto pred : right) rels.push_back(doQuery(pred, db, false));
    Relation result = Join(rels).Project(headVals);
    Relation orig = db.getRelation(head.id);
    vector<string> rSchema = result.getSchema();
    for (size_t ridx = 0; ridx < head.params.size(); ++ridx) {
        for (size_t sidx = 0; sidx < rSchema.size(); ++sidx) {
            if (head.params.at(ridx).value == rSchema.at(sidx)) {
                rSchema.at(sidx) = orig.getSchema().at(ridx);
            }
        }
    }
    Relation final = Relation(result.getName(), rSchema, result.getDatas());
    Union(final, orig, db);
}

void Querier::Union(Relation result, Relation orig, Database &db)
{
    set< vector<string> > bothDatas = orig.getDatas();
    for (auto rTup : result.getDatas()) bothDatas.insert(rTup);
    Relation both = Relation(orig.getName(), orig.getSchema(), bothDatas);
    db.modRelation(both);
}

Relation Querier::Join(vector<Relation> &rels)
{
    while (rels.size() > 1)
    {
        rels.at(0) = join(rels.at(0), rels.at(1));
        rels.erase(rels.begin()+1); // erase crossed relation
    }
    return rels.at(0);
}

Relation Querier::join(Relation first, Relation second) // correct version of join
{
    vector< pair<int,int> > dupes; // pair<index1, index2>
    set< vector<string> > datA = first.getDatas();
    set< vector<string> > datB = second.getDatas();
    vector<string> schA = first.getSchema();
    vector<string> schB = second.getSchema();
    for (size_t j = 0; j < schA.size(); ++j) {
        auto f = find(schB.begin(), schB.end(), schA.at(j)); // find duplicate
        if (f != schB.end()) dupes.push_back(pair<int,int>(j,f-schB.begin())); // save pair of indexes
    }
    if (!dupes.empty()) { // if there are duplicates
        first = Join(dupes, schA, schB, datA, datB, first.getName(), second.getName());
    } else {
        vector<Relation> toCross;
        toCross.push_back(first);
        toCross.push_back(second);
        first = cProduct(toCross); // if no duplicates, cross product
    }
    return first;
}

Relation Querier::Join(vector< pair<int,int> > &dupes, vector<string> &schA, vector<string> &schB,
    set< vector<string> > datA, set< vector<string> > datB, string nameA, string nameB)
{
    vector<string> newSchema = schA; // init new schema w/schema of A
    vector<int> dubs;
    for (auto p : dupes) dubs.push_back(p.second);
    sort(dubs.begin(), dubs.end());
    reverse(dubs.begin(), dubs.end());
    for (size_t b = 0; b < dubs.size(); ++b) schB.erase(schB.begin() + dubs.at(b)); // erase duplicate in schema B
    newSchema.insert(newSchema.end(), schB.begin(), schB.end()); // save rest of schema B
    set< vector<string> > newDatas = deDupe(datA, datB, dupes, dubs);
    string newName = nameA + nameB; // make name
    return Relation(newName, newSchema, newDatas);
}

set< vector<string> > Querier::deDupe(set< vector<string> > &datA, set< vector<string> > &datB,
    vector< pair<int, int> > &dupes, vector<int> &dubs)
{
    refine(datA, datB, dupes);
    set< vector<string> > newDatas;
    for (auto d : dupes) {
        for (auto a : datA) {
            for (auto b : datB) {
                if (a.at(d.first) == b.at(d.second)) {
                    for (auto s : dubs) {
                        b.erase(b.begin()+s);
                    }
                    vector<string> newTup = a;
                    newTup.insert(newTup.end(), b.begin(), b.end());
                    newDatas.insert(newTup);
                }
            }
        }
    }
    return newDatas;
}

void Querier::refine(set< vector<string> > &datA, set< vector<string> > &datB,
    vector< pair<int, int> > &dupes)
{
    for (auto p : dupes) { // iterate over duplicates found
        set< vector<string> > newDatasA; // init new datas
        set< vector<string> > newDatasB; // init new datas
        for (auto tupA : datA) { // iterate over tuples
            for (auto tupB : datB) {
                if (tupA.at(p.first) == tupB.at(p.second)) { // if duplicate
                    newDatasA.insert(tupA); // save tuple
                    newDatasB.insert(tupB); // save tuple
                }
            }
        }
        datA = newDatasA;
        datB = newDatasB;
    }
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
        Relation t = doQuery(queries.at(o), db, true);
    }
};

Relation Querier::doQuery(Predicate query, Database &db, bool print)
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
        if (print) printResult(temp, result);
        return temp;
    }
    if (print) printResult(result);
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

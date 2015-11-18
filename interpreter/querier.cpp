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
        doQueries(queries, db);
    }
};

void Querier::getSchemes(vector<Predicate> schemes, vector<Relation> &relations)
{
    for (vector<Predicate>::iterator st = schemes.begin(); st != schemes.end(); ++st) {
        string name = st->id;
        vector<Param> parms = st->params;
        vector<string> schema;
        for (size_t i = 0; i < parms.size(); ++i) {
            schema.push_back(parms.at(i).toString());
        }
        relations.push_back(Relation(name, schema));
    }
};

void Querier::getFacts(vector<Predicate> facts, vector<Relation> &relations)
{
    for (vector<Predicate>::iterator pt = facts.begin(); pt != facts.end(); ++pt) {
        for (size_t j = 0; j < relations.size(); ++j) {
            if (pt->id == relations.at(j).getName()) {
                vector<Param> parms = pt->params;
                vector<string> tups;
                for (size_t t = 0; t < parms.size(); ++t) {
                    if (parms.at(t).isString) tups.push_back(parms.at(t).toString());
                }
                relations.at(j).addTuple(tups);
            }
        }
    }
};

void Querier::doQueries(vector<Predicate> qs, Database db)
{
    vector< pair<string, vector< pair<string, string> > > > queries = getQueries(qs);
    for (size_t o = 0; o < queries.size(); ++o) {
        cout << qs.at(o).toString() << "?";
        Relation t = doQuery(queries.at(o), db);
    }
};

vector< pair<string, vector< pair<string, string> > > > Querier::getQueries(vector<Predicate> queries)
{
    ostringstream res;
    vector< pair<string, vector< pair<string, string> > > > quers;
    for (vector<Predicate>::iterator qt = queries.begin(); qt != queries.end(); ++qt) {
        string id = qt->id;
        vector<Param> prams = qt->params;
        vector< pair<string, string> > parms;
        res << qt->toString() << endl;
        for (size_t k = 0; k < prams.size(); ++k) {
            if(prams.at(k).isID) {
                parms.push_back(pair<string, string>(prams.at(k).value, "ID"));
            } else if (prams.at(k).isString) {
                parms.push_back(pair<string, string>(prams.at(k).value, "STR"));
            } else {
                parms.push_back(pair<string, string>(prams.at(k).value, "EXP"));
            }
        }
        quers.push_back(pair< string, vector< pair<string, string> > >(id, parms));
    }
    return quers;
};

Relation Querier::doQuery(pair<string, vector< pair<string, string> > > query, Database db)
{
    string id = query.first;
    vector< pair<string, string> > params = query.second;

    Relation r = db.getRelation(id);
    if (r.getName() == "NULL") return r;

    Relation result = r.Select(params);
    vector<string> ids;
    for (size_t r = 0; r < query.second.size(); ++r) {
        if (query.second.at(r).second == "ID") {
            ids.push_back(query.second.at(r).first);
        }
    }
    if (!ids.empty()) {
        Relation temp = result.Project(params);
        temp.Rename(ids);
        printResult(temp, result);
        return temp;
    }
    printResult(result);
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

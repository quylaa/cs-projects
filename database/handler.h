// Written by Aleks Christensen

#ifndef HANDLER_H_
#define HANDLER_H_

#include <utility>
#include "datalogProgram.h"
#include "database.h"

class Handler
{
public:
    Handler() {};
    ~Handler() {};

    string makeData(vector< vector<Predicate> > datas)
    {
        Database db;
        vector<Predicate> schemes = datas.at(0);
        vector<Predicate> facts = datas.at(1);
        vector<Predicate> queries = datas.at(2);
        vector<Relation> relations;

        getSchemes(schemes, relations);
        getFacts(facts, relations);

        for (vector<Relation>::iterator rt = relations.begin(); rt != relations.end(); ++rt) {
            db.addRelation((*rt));
        }
        string qdb = doQueries(queries, db);

        return qdb;
    };

    void getSchemes(vector<Predicate> schemes, vector<Relation> &relations)
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

    void getFacts(vector<Predicate> facts, vector<Relation> &relations)
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

    string doQueries(vector<Predicate> qs, Database db)
    {
        //Database results;
        ostringstream res;
        vector< pair<string, vector< pair<string, string> > > > queries = getQueries(qs);
//        for (vector< pair<string, vector< pair<string, string> > > >::iterator vpt = queries.begin();
//                vpt != queries.end(); ++vpt)
          for (size_t o = 0; o < queries.size(); ++o)
            {
                res << qs.at(o).toString();
                //results.addRelation(doQuery((*vpt), db));
                Relation t = doQuery(queries.at(o), db);
                if (t.getData().empty()) res << " No\n";
                else res << " Yes" << t.print();
            }
        return res.str();
    };

    vector< pair<string, vector< pair<string, string> > > > getQueries(vector<Predicate> queries)
    {
        vector< pair<string, vector< pair<string, string> > > > quers;
        for (vector<Predicate>::iterator qt = queries.begin(); qt != queries.end(); ++qt) {
            string id = qt->id;
            vector<Param> prams = qt->params;
            vector< pair<string, string> > parms;
            for (size_t k = 0; k < prams.size(); ++k) {
                if(prams.at(k).isID) {
                    parms.push_back(pair<string, string>(prams.at(k).value, "ID"));
                    cout << "GOT ID\n";
                } else if (prams.at(k).isString) {
                    parms.push_back(pair<string, string>(prams.at(k).value, "STR"));
                    cout << "GOT STR\n";
                } else {
                    parms.push_back(pair<string, string>(prams.at(k).value, "EXP"));
                    cout << "GOT EXP\n";
                }
            }
            quers.push_back(pair< string, vector< pair<string, string> > >(id, parms));
        }
        return quers;
    };

    Relation doQuery(pair<string, vector< pair<string, string> > > queries, Database db)
    {
        string id = queries.first;
        vector< pair<string, string> > params = queries.second;

        Relation r = db.getRelation(id);
        if (r.getName() == "NULL") return r;

        set< vector<string> > datas = r.Select(params);
        Relation temp(id, r.getSchema(), datas);
        vector< pair<int, bool> > areIds;
        for (size_t r = 0; r < queries.second.size(); ++r) {
            if (queries.second.at(r).second == "ID") {
                areIds.push_back(pair<int, bool>(r, true));
            }
        }
        if (!areIds.empty()) {
            map<string, vector<string> > proj = temp.Project(params);
            vector<string> schema;
            set< vector<string> > dat;
            for (map<string, vector<string> >::iterator vt = proj.begin(); vt != proj.end(); ++vt) {
                schema.push_back(vt->first);
                dat.insert(vt->second);
            }
            Relation temp(id, schema, dat);
            return temp;
        }
        // map<string, vector<string> > res = temp.Project(params);

        // for (vector< pair<string, string> >::iterator pt = params.begin(); pt != params.end(); ++pt) {
        //     string v = pt->first;
        //     string t = pt->second;
        //
        //     vector<string> parms;
        //
        //     if (t == "ID")
        // }

        return temp;
    };
};

#endif

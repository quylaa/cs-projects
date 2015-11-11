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

    void makeData(vector< vector<Predicate> > datas)
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
        doQueries(queries, db);
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

    void doQueries(vector<Predicate> qs, Database db)
    {
        vector< pair<string, vector< pair<string, string> > > > queries = getQueries(qs);
        for (size_t o = 0; o < queries.size(); ++o) {
            cout << qs.at(o).toString() << "?";
            Relation t = doQuery(queries.at(o), db);
            // if (t.getData().empty()) cout << " No\n";
            // else if (t.getData().size() == 1) {
            //     // if (!t.hasDone().at(2)) cout << " Yes(1)\n";
            //     /*else*/ cout << " Yes" << t.print();
            // }
            // else {
            //     cout << " Yes" << t.print();
            // }
        }
    };

    vector< pair<string, vector< pair<string, string> > > > getQueries(vector<Predicate> queries)
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

    Relation doQuery(pair<string, vector< pair<string, string> > > query, Database db)
    {
        string id = query.first;
        vector< pair<string, string> > params = query.second;

        Relation r = db.getRelation(id);
        if (r.getName() == "NULL") return r;

        Relation result = r.Select(params);
        // Relation temp(id, r.getSchema(), datas, r.hasDone());
        vector<string> ids;
        for (size_t r = 0; r < query.second.size(); ++r) {
            if (query.second.at(r).second == "ID") {
                ids.push_back(query.second.at(r).first);
            }
        }
        if (!ids.empty()) {
            Relation temp = result.Project(params);
            temp.Rename(ids);
            result = temp;
            if (result.getData().size() == 0) {
                cout << " No\n";
            } else {
                cout << " Yes(" << result.getData().size() << ")\n";
                cout << result.print();
            }
            return result;
        }
        if (result.getData().size() == 0) {
            cout << " No\n";
        } else if (result.getData().size() == 1) {
            cout << " Yes(1)\n";
        } else {
            cout << " Yes(" << result.getData().size() << ")\n";
            cout << result.print();
        }
        return result;
    };

    Relation queryPR(vector< pair<int, string> > ids, Relation temp, vector< pair<string, string> > params)
    {
        // map<string, vector<string> > proj = temp.Project(params);
        // vector<string> schema;
        // set< vector<string> > dat;
        // int l;
        // for (map<string, vector<string> >::iterator vt = proj.begin(); vt != proj.end(); ++vt) {
        //     schema.push_back(vt->first);
        //     l = vt->second.size();
        // }
        // cout << l << endl;
        // for (int m = 0; m < l; ++m) {
        //     vector<string> newt;
        //     for (map<string, vector<string> >::iterator vt = proj.begin(); vt != proj.end(); ++vt) {
        //             newt.push_back(vt->second.at(m));
        //     }
        //     dat.insert(newt);
        // }
        Relation newr = temp.Project(params);
        // if (areIds.size() == 1) {
        //     newr.Rename(schema.at(0), params.at(areIds.at(0).first).first);
        // } else {
        //     for (vector< pair<int, bool> >::iterator pt = areIds.begin(); pt != areIds.end(); ++pt) {
        //         if (pt->second == true) {
        //             newr.Rename(schema.at(pt->first), params.at(pt->first).first);
        //         }
        //     }
        // }
        return newr;
    };
};

#endif

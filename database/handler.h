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

    Database makeData(vector< vector<Predicate> > datas)
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

        return db;
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


};

#endif

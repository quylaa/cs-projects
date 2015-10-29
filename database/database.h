// Written by Aleks Christensen

#ifndef DATABASE_H_
#define DATABASE_H_

#include <string>
#include <vector>
#include <map>
#include "relation.h"

class Database
{
    private:
        map<string, Relation> allRelations;

    public:
        Database() {};
        ~Database() {};

        Relation getRelation(string name)
        {
            if (allRelations.find(name) != allRelations.end()) return allRelations.at(name);
            else {
                Relation none("NULL", vector<string>());
                return none;
            }
        };

        void addRelation(Relation rel)
        {
            string name = rel.getName();
            allRelations.insert(pair<string, Relation>(name, rel));
        };

        Relation doQuery();
};

#endif

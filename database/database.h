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

        Relation getRelation(string name);

        void addRelation(Relation rel);

        Relation doQuery();
};

#endif

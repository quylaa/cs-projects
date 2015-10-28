// Written by Aleks Christensen

#include "database.h"

Relation Database::getRelation(string name)
{
    if (allRelations.find(name) != allRelations.end()) return allRelations.at(name);
    else {
        Relation none("NULL", vector<string>());
        return none;
    }
}

void Database::addRelation(Relation rel)
{
    string name = rel.getName();
    allRelations.insert(pair<string, Relation>(name, rel));
}

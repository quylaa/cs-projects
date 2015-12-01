// Written by Aleks Christensen

#ifndef DATABASE_H_
#define DATABASE_H_

#include <string>
#include <sstream>
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

        void modRelation(Relation newRel)
        {
            string name = newRel.getName();
            allRelations.at(name) = newRel;
        };

        string print()
        {
            ostringstream out;
            for (map<string, Relation>::iterator mt = allRelations.begin(); mt != allRelations.end(); ++mt) {
                out << mt->first << "\n======\n" << mt->second.print();
            }
            return out.str();
        }
};

#endif

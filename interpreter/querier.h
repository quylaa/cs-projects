// Written by Aleks Christensen

#ifndef QUERIER_H_
#define QUERIER_H_

#include <utility>
#include "datalogProgram.h"
#include "database.h"

class Querier
{
public:
    Querier() {};
    ~Querier() {};

    void makeData(vector<Token> tokens);

    void getSchemes(vector<Predicate> schemes, vector<Relation> &relations);

    void getFacts(vector<Predicate> facts, vector<Relation> &relations);

    void doRules(vector<Rule> rules, Database &db);

    Relation join(vector<Relation> rels);

    Relation natJoin(Relation rel);

    Relation cProduct(vector<Relation> rels);

    void doQueries(vector<Predicate> qs, Database &db);

    Relation doQuery(Predicate query, Database &db);

    void printResult(Relation result);

    void printResult(Relation result, Relation prev);

    bool schemaComp(Relation A, Relation B);
};

#endif

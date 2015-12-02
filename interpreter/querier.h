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

    Relation Join(vector<Relation> &rels);

    Relation join(Relation first, Relation second);

    // Relation natJoin(Relation rel);

    void Union(Relation result, Relation orig, Database &db);

    Relation cProduct(vector<Relation> rels);

    void doQueries(vector<Predicate> qs, Database &db);

    Relation doQuery(Predicate query, Database &db, bool print);

    void printResult(Relation result);

    void printResult(Relation result, Relation prev);

    bool schemaComp(Relation A, Relation B);
};

#endif

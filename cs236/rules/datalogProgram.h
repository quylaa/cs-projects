// Written by Aleks Christensen

#ifndef DATALOGPROGRAM_H_
#define DATALOGPROGRAM_H_

#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include "token.h"
#include "rule.h"
#include "predicate.h"

using namespace std;

class datalogProgram
{
    private:
        // ostringstream out;
        vector<Token> vt;

        vector<Predicate> schemes;
        vector<Predicate> facts;
        vector<Rule> rules;
        vector<Predicate> queries;

        int index = 0;

    public:

        datalogProgram();
        ~datalogProgram();

        /*
         * parser
         *
         * Attempts to parse the given tokens into a recognized language
         *
         */
        bool parse(vector<Token> tokens);

        void scheme();

        void schemeList();

        void idList(vector<Param> &parms);

        void fact();

        void factList();

        void rule();

        void ruleList();

        Predicate headPredicate();

        Predicate predicate();

        void predicateList(vector<Predicate> &rules);

        Param parameter();

        void parameterList(vector<Param> &parms);

        Param expression();

        string op();

        void query();

        void queryList();

        void stringList(vector<Param> &parms);

        void match(string type);

        vector<string> domain();

        bool isIn(vector<string> dv, string s);

        string schemesToString();

        string factsToString();

        string rulesToString();

        string queriesToString();

        string domainToString(vector<string> dv);

        /*
         * toString
         *
         * Converts everything to a string
         *
         */
        string toString();

        vector< vector<Predicate> > toDatabase();

        vector<Predicate> getSchemes();

        vector<Predicate> getFacts();

        vector<Rule> getRules();

        vector<Predicate> getQueries();
};

#endif

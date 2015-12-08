// Written by Aleks Christensen

#ifndef DEPEND_H_
#define DEPEND_H_

#include <string>
#include <vector>
#include <map>
#include <set>
#include <utility>
#include <iostream>
#include "node.h"

using namespace std;

class Depend
{
private:
    // map<int, set<int> > base;
    // map<int, set<int> > reverse;
    // map<int, set<Node> > depGraph;

public:

    Depend();
    ~Depend();

    vector<int> optimize(vector<Rule> rules);

    map<int, set<int> > drawGraph(vector<Rule> rules);

    map<int, set<int> > revGraph(map<int, set<int> > base);

    set<int> getDepends(Rule r, vector<Rule> rules);

};

#endif

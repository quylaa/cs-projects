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
    map<int, set<Node> > depGraph;

public:

    Depend();
    ~Depend();

    map<int, set<int> > drawGraph(vector<Rule> rules);

    set<int> getDepends(Rule r, vector<Rule> rules);

};

#endif

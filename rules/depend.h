// Written by Aleks Christensen

#ifndef DEPEND_H_
#define DEPEND_H_

#include "node.h"
#include <string>
#include <vector>
#include <map>
#include <set>

using namespace std;

class Depend
{
private:
    map<int, set<Node> > depGraph;

public:

    Depend();
    ~Depend();

    map<int, set<Node> > drawGraph(vector<Rule> rules);

    vector<int> getDepends(Rule r, vector<Rule> rules);

};

#endif

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
    map<int, set<Node> > forward;
    map<int, set<Node> > reverse;

public:

    Depend();
    ~Depend();

    vector<int> optimize(vector<Rule> rules);

    vector<Node> drawGraph(vector<Rule> rules);

    vector<Node> revGraph(vector<Node> base);

    set<int> getDepends(Rule r, vector<Rule> rules);

    vector<Node> DFS(map<int, set<int> > graph, vector<Node> &nodes);

};

#endif

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
    vector<Node> forward;
    vector<Node> reverse;
    int PO;

public:

    Depend();
    ~Depend();

    vector<int> optimize(vector<Rule> rules);

    vector<Node> drawGraph(vector<Rule> rules);

    vector<Node> revGraph(vector<Node> base);

    set<int> getDepends(Rule r, vector<Rule> rules);

    // Usage:- for n in nodes: DFS(n)
    void DFS(int node);

};

#endif

// Written by Aleks Christensen

#include "depend.h"

Depend::Depend() {};
Depend::~Depend() {};

map<int, set<Node> > Depend::drawGraph(vector<Rule> rules)
{
    map<int, set<Node> > deps;
    set<Node> nodes;
    for (size_t r = 0; r < rules.size(); ++r) {
        Node n = Node(false, r, rules.at(r).head.id, rules.at(r));
        nodes.insert(n);
    }
    for (auto n : nodes) {

    }

    return deps;
}

vector<int> getDepends(Rule r, vector<Rule> rules)
{
    vector<int> deps;
    for (size_t p = 0; p < r.rules.size(); ++p) {
        for (size_t rule = 0; rule < rules.size(); ++rule) {
            if (r.rules.at(p).id == rules.at(rule).head.id) deps.push_back(rule);
        }
    }
    return deps;
}

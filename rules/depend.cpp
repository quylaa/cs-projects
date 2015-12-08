// Written by Aleks Christensen

#include "depend.h"

Depend::Depend() {};
Depend::~Depend() {};

vector<int> Depend::optimize(vector<Rule> rules)
{
    vector<int> order;
    vector<Node> rev = revGraph(drawGraph(rules));

    return order;
}

vector<Node> Depend::drawGraph(vector<Rule> rules)
{
    // vector<Node> deps; // map of rule -> dependencies, where the set is the rule numbers that are depended on
    vector<Node> nodes;
    for (size_t r = 0; r < rules.size(); ++r) {
        Node n = Node(/*false, r, */r/*, rules.at(r)*/);
        nodes.push_back(n); // make a node for all rules
    }

    for (size_t i = 0; i < rules.size(); ++i) {
        nodes.at(i).deps = getDepends(rules.at(i), rules);
    }

    for (auto n : nodes) {
        cout << "R" << n.ruleNum << ": ";
        for (auto d : n.deps) { // debugging
            cout << "R" << d;
            if (d != (*--n.deps.end())) cout << ",";
        }
        cout << endl;
    }
    cout << "//" << endl;

    // baseGraph = deps;
    return nodes;
}

vector<Node> Depend::revGraph(vector<Node> nodes)
{
    vector<Node> rev = nodes;

    for (int b = 0; (size_t)b < nodes.size(); ++b) {
        set<int> de;
        for (auto r : nodes) {
            for (auto d : r.deps) {
                if (b == d) de.insert(r.ruleNum);
            }
        }
        // rev.insert(pair<int, set<int> >(b, de));
        rev.at(b).deps = de;
    }

    for (auto n : rev) {
        cout << "R" << n.ruleNum << ": ";
        for (auto d : n.deps) { // debugging
            cout << "R" << d;
            if (d != (*--n.deps.end())) cout << ",";
        }
        cout << endl;
    }
    cout << "//" << endl;

    return rev;
}

set<int> Depend::getDepends(Rule r, vector<Rule> rules)
{
    set<int> deps; // init set of dependencies
    for (size_t p = 0; p < r.rules.size(); ++p) { // for all predicates in tail of rule
        for (size_t rule = 0; rule < rules.size(); ++rule) { // iterate over all rules
            if (r.rules.at(p).id == rules.at(rule).head.id) deps.insert(rule); // if any are matched, add to set
        }
    }
    return deps;
}

vector<Node> Depend::DFS(map<int, set<int> > graph, vector<Node> &nodes)
{
    vector<Node> n;



    return n;
}

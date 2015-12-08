// Written by Aleks Christensen

#include "depend.h"

Depend::Depend() {};
Depend::~Depend() {};

vector<int> Depend::optimize(vector<Rule> rules)
{
    vector<int> order;
    map<int, set<int> > rev = revGraph(drawGraph(rules));

    return order;
}

map<int, set<int> > Depend::drawGraph(vector<Rule> rules)
{
    map<int, set<int> > deps; // map of rule -> dependencies, where the set is the rule numbers that are depended on
    vector<Node> nodes;
    for (size_t r = 0; r < rules.size(); ++r) {
        Node n = Node(/*false, r, */rules.at(r).head.id, rules.at(r));
        nodes.push_back(n); // make a node for all rules
    }

    for (size_t i = 0; i < rules.size(); ++i) {
        deps.insert(pair<int, set<int> >(i, getDepends(rules.at(i), rules)));
    }

    for (auto d : deps) { // debugging
        cout << "R" << d.first << ": ";
        for (auto n = d.second.begin(); n != d.second.end(); ++n) {
            cout << "R" << (*n);
            if (next(n) != d.second.end()) cout << ",";
        }
        cout << endl;
    }
    cout << "//" << endl;

    // baseGraph = deps;
    return deps;
}

map<int, set<int> > Depend::revGraph(map<int, set<int> > base)
{
    map<int, set<int> > rev;

    for (int b = 0; (size_t)b < base.size(); ++b) {
        set<int> de;
        for (auto r : base) {
            for (auto d : r.second) {
                if (b == d) de.insert(r.first);
            }
        }
        rev.insert(pair<int, set<int> >(b, de));
    }

    for (auto d : rev) { // debugging
        cout << "R" << d.first << ": ";
        for (auto n = d.second.begin(); n != d.second.end(); ++n) {
            cout << "R" << (*n);
            if (next(n) != d.second.end()) cout << ",";
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

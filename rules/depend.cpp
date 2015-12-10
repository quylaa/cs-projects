// Written by Aleks Christensen

#include "depend.h"

Depend::Depend() {};
Depend::~Depend() {};

vector<SCC> Depend::optimize(vector<Rule> rules)
{
    vector<SCC> order;
    vector<Node> rev = revGraph(drawGraph(rules)); // get both graph and reverse graph
    PO = 0; // init post-order number counter
    for (int d = 0; (size_t)d < reverse.size(); ++d) DFS(d); // do depth-first search
    poSave();

    for (int p = (PO-1); p >= 0; --p) {
        S.clear();
        scc(p);
        if (S.empty()) continue;

        if (S.size() == 1 && trivial(p)) order.push_back(SCC(S, true));
        else order.push_back(SCC(S, false));
    }

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

    cout << "Dependency Graph" << endl;
    for (auto n : nodes) {
        cout << "R" << n.ruleNum << ":";
        for (auto d : n.deps) { // debugging
            cout << "R" << d;
            if (d != (*--n.deps.end())) cout << ",";
        }
        cout << endl;
    }
    cout << endl;

    forward = nodes;
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
        rev.at(b).deps = de;
    }

    reverse = rev;
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

void Depend::poSave()
{
    for (int f = 0; (size_t)f < forward.size(); ++f) { // save post-order numbers to original graph nodes
        for (int r = 0; (size_t)r < reverse.size(); ++r) {
            if (forward.at(f).ruleNum == reverse.at(r).ruleNum)
                forward.at(f).poNum = reverse.at(r).poNum;
        }
    }
}

void Depend::DFS(int node)
{
    if (reverse.at(node).visited) return;
    reverse.at(node).visited = true;

    for (auto d : reverse.at(node).deps) DFS(d);
    reverse.at(node).poNum = PO;
    PO++;
}

void Depend::dfs(int node)
{
    if (forward.at(node).visited) return;
    forward.at(node).visited = true;

    for (auto d : forward.at(node).deps) dfs(d);

    S.insert(forward.at(node).ruleNum);
}

void Depend::scc(int ponum)
{
    int k = getIndex(ponum);

    if (k == -1 || forward.at(k).visited) return;
    forward.at(k).visited = true;

    for (auto d : forward.at(k).deps) dfs(d);

    S.insert(forward.at(k).ruleNum);
}

int Depend::getIndex(int ponum)
{
    for (int p = 0; (size_t)p < forward.size(); ++p)
        if (forward.at(p).poNum == ponum) return p;
    return -1;
}

bool Depend::trivial(int ponum)
{
    int k = getIndex(ponum);

    if (k == -1) return false;

    for (auto d : forward.at(k).deps) if (k == d) return false;
    return true;
}

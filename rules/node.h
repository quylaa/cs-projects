// Written by Aleks Christensen

#ifndef NODE_H_
#define NODE_H_

#include <set>
#include "rule.h"

class Node
{
public:
    bool visited;
    // bool revisit;
    int poNum;
    int ruleNum;
    Rule rule;
    std::set<int> deps;

    Node(/*bool v, int p, */int n/*, Rule r*/) :
        visited(false),/* revisit(false), poNum(p), rule(r),*/ ruleNum(n) {};
};

#endif

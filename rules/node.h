// Written by Aleks Christensen

#ifndef NODE_H_
#define NODE_H_

#include <string>
#include "rule.h"

class Node
{
public:
    bool visited;
    int poNum;
    std::string name;
    Rule rule;

    Node(/*bool v, int p, */std::string n, Rule r) : visited(false),/* poNum(p),*/ name(n), rule(r) {};
};

#endif

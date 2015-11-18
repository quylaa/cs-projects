// Written by Aleks Christensen

#ifndef RULE_H_
#define RULE_H_

#include "predicate.h"

class Rule
{
public:
    Predicate head;
    std::vector<Predicate> rules;

    Rule(){}

    std::string toString()
    {
        std::string o;
        o.append(head.toString());
        o.append(" :- ");
        for (size_t i = 0; i < rules.size(); ++i) {
            o.append(rules.at(i).toString());
            if (i == rules.size()-1) break;
            o.append(",");
        }
        o.append(".");
        return o;
    }
};

#endif

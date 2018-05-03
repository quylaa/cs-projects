// Written by Aleks Christensen

#ifndef PREDICATE_H_
#define PREDICATE_H_

#include <vector>
#include "param.h"

class Predicate
{
public:
        std::string id;
        std::vector<Param> params;

        Predicate(){}

        std::string toString()
        {
            std::string o;
            o.append(id);
            o.append("(");
            for (size_t i = 0; i < params.size(); ++i) {
                o.append(params.at(i).toString());
                if (i == params.size()-1) break;
                o.append(",");
            }
            o.append(")");
            return o;
        }
};

#endif

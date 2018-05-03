// Written by Aleks Christensen

#ifndef PARAM_H_
#define PARAM_H_

#include <string>

struct Param
{
public:
    std::string value;
    bool isID;
    bool isString;

    Param(std::string v, bool isid, bool iss) : value(v), isID(isid),
        isString(iss) {};

    std::string toString()
    {
        return value;
    }
};

#endif

// Written by Aleks Christensen

#ifndef SCC_H_
#define SCC_H_

#include <set>

class SCC
{
public:
    std::set<int> scc;
    bool trivial;

    SCC(std::set<int> s, bool t) : scc(s), trivial(t) {}
    ~SCC() {}
};


#endif

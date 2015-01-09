// Written by Aleks Christensen

#pragma once
#include "ArenaInterface.h"

class Arena : public ArenaInterface
{
    private:
        string name;
        vector<FighterInterface*> fighters;

    public:
        Arena(string name){}
        virtual ~Arena(){}

        bool addFighter(string info);

        bool removeFighter(string);

        FighterInterface* getFighter(string name) const;

        int getSize() const;
};

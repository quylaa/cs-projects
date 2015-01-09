// Written by Aleks Christensen

#pragma once
#include "ArenaInterface.h"

class Arena : public ArenaInterface
{
    private:
        vector<FighterInterface*> fighters;

    public:
        Arena();
        virtual ~Arena();

        bool addFighter(string info);

        bool removeFighter(string);

        FighterInterface* getFighter(string name) const;

        int getSize() const;
};

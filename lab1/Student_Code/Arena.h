// Written by Aleks Christensen

#ifndef ARENA_DEF
#define ARENA_DEF
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

        FighterInterface* getFighter(string name);

        int getSize();
};
#endif

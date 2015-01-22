// Written by Aleks Christensen

#ifndef ARCHER_DEF
#define ARCHER_DEF
#include "Fighter.h"

class Archer : public Fighter
{
    private:
        int baseSpd;

    public:
        Archer(string info);
        virtual ~Archer();

        int getDamage();

        void reset();

        bool useAbility();
};
#endif

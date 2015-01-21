// Written by Aleks Christensen

#ifndef CLERIC_DEF
#define CLERIC_DEF
#include "Fighter.h"

class Cleric : public Fighter
{
    private:
        int mana;

    public:
        Cleric(string info);
        virtual ~Cleric();

        int getDamage();

        void reset();

        void regenerate();

        bool useAbility();
};
#endif

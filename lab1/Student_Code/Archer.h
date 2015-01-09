// Written by Aleks Christensen

// #pragma once
#include "Fighter.h"

class Archer : public Fighter
{
    private:
        int bonus;

    public:
        Archer(string info);
        virtual ~Archer();

        int getDamage();

        void reset();

        void regenerate();

        bool useAbility();
};
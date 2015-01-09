// Written by Aleks Christensen

#pragma once
#include "Fighter.h"

class Cleric : public Fighter
{
    private:
        int mana;

    public:
        Cleric(string info){}
        virtual ~Cleric(){}

        int getDamage();

        void reset();

        void regenerate();

        bool useAbility();
};
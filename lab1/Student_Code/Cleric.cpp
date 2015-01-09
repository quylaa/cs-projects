// Written by Aleks Christensen

#include "Cleric.h"

Cleric::Cleric(string info) : Fighter(info)
{
    mana = 5 * mgc;
}
Cleric::~Cleric(){}

int Cleric::getDamage()
{
    return mgc;
}

void Cleric::reset()
{
    Fighter::reset();
    mana = 5 * mgc;
}

bool Cleric::useAbility()
{
    if (mana < CLERIC_ABILITY_COST) return false;
    else {
        int inc = mgc / 3;
        if (inc < 1) inc = 1;
        curHP += inc;
        if (curHP > maxHP) curHP = maxHP;
        mana -= CLERIC_ABILITY_COST;
        return true;
    }
}
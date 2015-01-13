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

void Cleric::regenerate()
{
  Fighter::regenerate();
  int inc = mana / 5;
  if (inc < 1) inc = 1;
  mana += inc;
  if (mana > (mgc * 5)) mana = mgc * 5;
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
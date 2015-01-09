// Written by Aleks Christensen

#include "Archer.h"

Archer::Archer(string info) : Fighter(info)
{
    bonus = 0;
}
Archer::~Archer(){}

int Archer::getDamage()
{
    return (spd + bonus);
}

void Archer::reset()
{
    Fighter::reset();
    bonus = 0;
}

bool Archer::useAbility()
{
    bonus++;
    return true;
}
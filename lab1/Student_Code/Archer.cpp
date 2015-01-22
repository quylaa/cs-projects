// Written by Aleks Christensen

#include "Archer.h"

Archer::Archer(string info) : Fighter(info)
{
    baseSpd = spd;
}
Archer::~Archer(){}

int Archer::getDamage()
{
    return spd;
}

void Archer::reset()
{
    Fighter::reset();
    spd = baseSpd;
}

bool Archer::useAbility()
{
    spd++;
    return true;
}

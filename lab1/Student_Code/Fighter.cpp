// Written by Aleks Christensen

#include "Fighter.h"

Fighter::Fighter(string info) : FighterInterface()
{
    istringstream iss(info);
    vector<string> tokens{ istream_iterator < string > {iss}, istream_iterator < string > {} }; // separate info string into words
    name = tokens.at(NAME_LOC);
    type = tokens.at(TYPE_LOC);
    maxHP = stoi(tokens.at(HP_LOC));
    str = stoi(tokens.at(STR_LOC));
    spd = stoi(tokens.at(SPD_LOC));
    mgc = stoi(tokens.at(MGC_LOC));
    curHP = maxHP;
}
Fighter::~Fighter(){}

string Fighter::getName()
{
    return name;
}

int Fighter::getMaximumHP()
{
    return maxHP;
}

int Fighter::getCurrentHP()
{
    return curHP;
}

int Fighter::getStrength()
{
    return str;
}

int Fighter::getSpeed()
{
    return spd;
}

int Fighter::getMagic()
{
    return mgc;
}

int Fighter::getDamage()
{
    return 0;
}

void Fighter::takeDamage(int damage)
{
    int dmg = damage - (spd / 4);
    if (dmg < 1) dmg = 1;
    curHP -= dmg;
}

void Fighter::reset()
{
    curHP = maxHP;
}

void Fighter::regenerate()
{
    int inc = str / 6;
    if (inc < 1) inc = 1;
    curHP += inc;
    if (curHP > maxHP) curHP = maxHP;
}

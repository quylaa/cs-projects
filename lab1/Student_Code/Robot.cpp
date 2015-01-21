// Written by Aleks Christensen

#include "Robot.h"

Robot::Robot(string info) : Fighter(info)
{
    bonus = 0;
    maxEng = 2 * mgc;
    curEng = maxEng;
}
Robot::~Robot(){}

int Robot::getDamage()
{
    return (str + bonus);
    this->bonus = 0;
}

void Robot::reset()
{
    Fighter::reset();
    curEng = maxEng;
}

bool Robot::useAbility()
{
    if (this->bonus != 0) return false;
    if (curEng < ROBOT_ABILITY_COST) return false;
    else {
        double bonDmg = (str * pow((curEng / maxEng), 4));
        bonus = bonDmg;
        curEng -= ROBOT_ABILITY_COST;
        return true;
    }
}

int Robot::getCurEng()
{
    return curEng;
}

int Robot::getMaxEng()
{
    return maxEng;
}

int Robot::getBonus()
{
    return bonus;
}

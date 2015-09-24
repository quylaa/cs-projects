// Written by Aleks Christensen

#include "Robot.h"

Robot::Robot(string info) : Fighter(info)
{
    bonus = 0;
	eng = 2 * mgc;
}
Robot::~Robot(){}

int Robot::getDamage()
{
	int dmg = str + bonus;
	bonus = 0;
    return dmg;
}

void Robot::reset()
{
    Fighter::reset();
	eng = 2 * mgc;
	bonus = 0;
}

bool Robot::useAbility()
{
    if (bonus != 0) return false;
    if (eng < ROBOT_ABILITY_COST) return false;
    else {
		double bonDmg = eng / (2.0 * mgc);
        bonDmg = (str * pow(bonDmg, 4));
        bonus = bonDmg;
        eng -= ROBOT_ABILITY_COST;
        return true;
    }
}

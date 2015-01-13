// Written by Aleks Christensen

#ifndef FIGHTER_DEF
#define FIGHTER_DEF
#include <sstream>
#include "FighterInterface.h"

const int NAME_LOC = 0;
const int TYPE_LOC = 1;
const int HP_LOC = 2;
const int STR_LOC = 3;
const int SPD_LOC = 4;
const int MGC_LOC = 5;

class Fighter : public FighterInterface
{
    protected:
        string name;
        string type;
        int maxHP;
        int curHP;
        int str;
        int spd;
        int mgc;

    public:
        Fighter(string info);
        virtual ~Fighter();

        /*
        *	getName()
        *
        *	Returns the name of this fighter.
        */
        string getName();

        /*
        *	getMaximumHP()
        *
        *	Returns the maximum hit points of this fighter.
        */
        int getMaximumHP();

        /*
        *	getCurrentHP()
        *
        *	Returns the current hit points of this fighter.
        */
        int getCurrentHP();

        /*
        *	getStrength()
        *
        *	Returns the strength stat of this fighter.
        */
        int getStrength();

        /*
        *	getSpeed()
        *
        *	Returns the speed stat of this fighter.
        */
        int getSpeed();

        /*
        *	getMagic()
        *
        *	Returns the magic stat of this fighter.
        */
        int getMagic();

        /*
        *	getDamage()
        *
        *	Returns the amount of damage a fighter will deal.
        *
        *	Robot:
        *	This value is equal to the Robot's strength plus any additional damage added for having just used its special ability.
        *
        *	Archer:
        *	This value is equal to the Archer's speed.
        *
        *	Cleric:
        *	This value is equal to the Cleric's magic.
        */
        virtual int getDamage();

        /*
        *	takeDamage(int)
        *
        *	Reduces the fighter's current hit points by an amount equal to the given
        *	damage minus one fourth of the fighter's speed.  This method must reduce
        *	the fighter's current hit points by at least one.  It is acceptable for
        *	this method to give the fighter negative current hit points.
        *
        */
        void takeDamage(int damage);

        /*
        *	reset()
        *
        *	Restores a fighter's current hit points to its maximum hit points.
        *
        *	Robot:
        *	Also restores a Robot's current energy to its maximum value (which is 2 times its magic).
        *	Also resets a Robot's bonus damage to 0.
        *
        *	Archer:
        *	Also resets an Archer's current speed to its original value.
        *
        *	Cleric:
        *	Also restores a Cleric's current mana to its maximum value (which is 5 times its magic).
        */
        virtual void reset();

        /*
        *	regenerate()
        *
        *	Increases the fighter's current hit points by an amount equal to one sixth of
        *	the fighter's strength.  This method must increase the fighter's current hit
        *	points by at least one.  Do not allow the current hit points to exceed the
        *	maximum hit points.
        *
        *	Cleric:
        *	Also increases a Cleric's current mana by an amount equal to one fifth of the
        *	Cleric's magic.  This method must increase the Cleric's current mana by at
        *	least one.  Do not allow the current mana to exceed the maximum mana.
        */
        virtual void regenerate();

        /*
        *	useAbility()
        *
        *	Attempts to perform a special ability based on the type of fighter.  The
        *	fighter will attempt to use this special ability just prior to attacking
        *	every turn.
        *
        */
        virtual bool useAbility() = 0;
};
#endif
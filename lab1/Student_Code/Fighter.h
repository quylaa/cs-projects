// Written by Aleks Christensen

#pragma once
#include "FighterInterface"

Class Fighter : Public FighterInterface
{
    private:
        string name;
        string type;
        int maxHP;
        int curHP;
        int str;
        int spd;
        int mgc;

    public:
        Fighter(string info){}
        virtual ~Fighter(){}

        string getname() const;

        int getMaximumHP() const;

        int getCurrentHP() const;

        int getStrength() const;

        int getSpeed() const;

        int getMagic() const;

        int getDamage();

        void takeDamage(int damage);

        void reset();

        void regenerate();

        bool useAbility();
};

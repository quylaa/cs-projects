// Written by Aleks Christensen

// #pragma once
#include "Fighter.h"

class Robot : public Fighter
{
    private:
        int bonus;
        int maxEng;
        int curEng;

    public:
        Robot(string info);
        virtual ~Robot();

        int getDamage();

        void reset();

        void regenerate();

        bool useAbility();
};
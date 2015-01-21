// Written by Aleks Christensen

#ifndef ROBOT_DEF
#define ROBOT_DEF
#include "Fighter.h"

class Robot : public Fighter
{
    private:
        int bonus;
        int eng;

    public:
        Robot(string info);
        virtual ~Robot();

        int getDamage();

        void reset();

        bool useAbility();
};
#endif

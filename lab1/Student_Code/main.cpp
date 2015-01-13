// Written by Aleks Christensen

#include "Arena.h"
#include "Robot.h"
#include "Archer.h"
#include "Cleric.h"

int main()
{
    Arena* stadium = new Arena();
    stadium->addFighter("John C 100 3 6 20");
    stadium->getFighter("John");
    delete stadium;
    return 0;
}
// Written by Aleks Christensen

#include "Arena.h"
#include "Robot.h"
#include "Archer.h"
#include "Cleric.h"

int main()
{
    Arena* stadium = new Arena();
    stadium->addFighter("John C 100 3 6 20");
    stadium->addFighter("Bob R 150 20 8 12");
    FighterInterface* first = stadium->getFighter("John");
    FighterInterface* second = stadium->getFighter("Bob");
    cout << first->getName() << endl;
    cout << second->getName() << endl;
    delete first;
    delete second;
    stadium->removeFighter("John");
    stadium->removeFighter("Bob");

    delete stadium;
    return 0;
}

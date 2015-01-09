// Written by Aleks Christensen

#include "Arena.h"

Arena::Arena(string aname) : ArenaInterface(){
    name = aname;
    vector<FighterInterface*> fighters;
};
Arena::~Arena(){};

bool Arena::addFighter(string info)
{
    Fighter* fighter = new Fighter(info);
    fighters.push_back(fighter);
    delete fighter;
    return true;
}

bool Arena::removeFighter(string name)
{
    vector<FighterInterface*>::iterator roster;
    for (roster = fighters.begin(); roster != fighters.end(); ++roster) {
        if ((*roster)->getName() == name) {
            delete * roster;
            roster = fighters.erase(roster);
            return true;
        }
    }
    return false;
}

FighterInterface* Arena::getFighter(string name) const
{
    vector<FighterInterface*>::iterator roster;
    for (roster = fighters.begin(); roster != fighters.end(); ++roster) {
        if ((*roster)->getName() == name) {
            FighterInterface* fighter = roster;
        }
    }
    return fighter;
}

int Arena::getSize() const
{
    return fighters.size();
}

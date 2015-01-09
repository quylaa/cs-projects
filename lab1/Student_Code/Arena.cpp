// Written by Aleks Christensen

#include "Arena.h"
#include "Robot.h"
#include "Archer.h"
#include "Cleric.h"

Arena::Arena() : ArenaInterface(){
    vector<FighterInterface*> fighters;
}
Arena::~Arena(){}

bool Arena::addFighter(string info)
{
    istringstream iss(info);
    vector<string> tokens{ istream_iterator<string>{iss}, istream_iterator<string>{} };
    if (tokens.at(TYPE_LOC) != "R" && tokens.at(TYPE_LOC) != "A" && tokens.at(TYPE_LOC) != "C") return false;
    if (!stoi(tokens.at(HP_LOC))) return false;
    if (!stoi(tokens.at(STR_LOC))) return false;
    if (!stoi(tokens.at(SPD_LOC))) return false;
    if (!stoi(tokens.at(MGC_LOC))) return false;
    if (tokens.at(TYPE_LOC) == "R") {
      Robot* rob = new Robot(info);
      fighters.push_back(rob);
    }
    if (tokens.at(TYPE_LOC) == "A") {
      Archer* arc = new Archer(info);
      fighters.push_back(arc);
    }
    if (tokens.at(TYPE_LOC) == "C") {
      Cleric* clr = new Cleric(info);
      fighters.push_back(clr);
    }
    //Fighter* ftr = new Fighter(info);
    //fighters.push_back(ftr);
    //delete ftr;
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
    //for (roster = fighters.begin(); roster != fighters.end(); ++roster) {
    //    if ((*roster)->getName() == name) {
    //        FighterInterface* ftr = (*roster);
    //    }
    //}
    //return ftr;
}

int Arena::getSize() const
{
    return fighters.size();
}

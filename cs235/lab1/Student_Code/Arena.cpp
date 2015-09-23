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
    vector<string> tokens{ istream_iterator<string>{iss}, istream_iterator<string>{} }; // extract words from input string into vector
    if (tokens.size() != 6) return false; // if vector is too small, reject input
    if (tokens.at(TYPE_LOC) != "R" && tokens.at(TYPE_LOC) != "A" && tokens.at(TYPE_LOC) != "C") return false; // if fighter type is invalid, reject input
    if (!stoi(tokens.at(HP_LOC))) return false; // if any of the numbers do not cast to int, reject input
    if (!stoi(tokens.at(STR_LOC))) return false;
    if (!stoi(tokens.at(SPD_LOC))) return false;
    if (!stoi(tokens.at(MGC_LOC))) return false;

    for (size_t man = 0; man < fighters.size(); ++man) { // check to see if fighter already exists with that name
        if (fighters.at(man)->getName() == tokens.at(NAME_LOC)) return false;
    }

    for (int stat = HP_LOC; stat < tokens.size(); ++stat) { // if any stats are doubles, reject input
      if (stod(tokens.at(stat)) != stoi(tokens.at(stat))) return false;
    }

    if (tokens.at(TYPE_LOC) == "R") { // create fighter
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

FighterInterface* Arena::getFighter(string name)
{
    for (size_t roster = 0; roster < fighters.size(); ++roster) {
       if (fighters.at(roster)->getName() == name) {
           FighterInterface* ftr = fighters.at(roster);
           return ftr;
       }
    }
	// FighterInterface* null = new Robot("NULL R 0 0 0 0");
	// return null;
}

int Arena::getSize()
{
    return fighters.size();
}

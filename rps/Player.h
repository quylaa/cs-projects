// Written by Aleks Christensen
#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <ctime>

using namespace std;

class Player
{
  private:
    string name;
    int wins;
    int losses;
    int draws;

  public:
    /* Constructor of the Player class
     *
     * nameIn will be set to the name of the player
     */
    Player(string nameIn);
    virtual ~Player();
    // -----------------------------------
    /* getRPSThrow
     *
     * Returns the player's choice in a match
     */
    string getRPSThrow();
    /*
     * getWinRecord
     *
     * Returns the player's W:L ratio
     */
    double getWinRecord();
    /*
     * toString
     *
     * Returns a string of all the player's information
     */
    string toString();

};

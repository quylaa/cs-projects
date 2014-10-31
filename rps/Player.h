// Written by Aleks Christensen
#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <ctime>

using namespace std;

class Player
{
  private:
    string name;
    int matches;
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
    /* getName
     *
     * Returns the player's name
     */
    string getName();
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
    /* addRecord
     *
     * Adds a match and either a win, loss, or draw to a player's record
     */
    void addRecord(string op);
    /*
     * toString
     *
     * Returns a string of all the player's information
     */
    string toString();

};

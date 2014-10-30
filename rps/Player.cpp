// Written by Aleks Christensen
#include "Player.h"

using namespace std;

const string throws[3] = {"rock", "paper", "scissors"};

Player::Player(string nameIn)
{
  name = nameIn;
  wins = 0;
  losses = 0;
  draws = 0;
}
Player::~Player(){}

string Player::getRPSThrow()
{
  return throws[rand() % 3 + 1];
}

double Player::getWinRecord()
{
  return wins / losses;
}

string Player::toString()
{
  stringstream info;
  info << "Name: " << name << endl;
  info << "Wins: " << wins << endl;
  info << "Losses: " << losses << endl;
  info << "Draws: " << draws << endl;
  return info.str();
}

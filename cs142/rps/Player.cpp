// Written by Aleks Christensen
#include "Player.h"

using namespace std;

const string throws[3] = {"rock", "paper", "scissors"};

Player::Player(string nameIn)
{
  name = nameIn;
  matches = 0;
  wins = 0;
  losses = 0;
  draws = 0;
}
Player::~Player(){}

string Player::getName() const
{
  return name;
}

string Player::getRPSThrow() const
{
  int r = rand() % 3;
  return throws[r];
}

double Player::getWinRecord() const
{
  return wins / losses;
}

void Player::addRecord(string op)
{
  matches ++;
  if (op == "win") {
    wins++;
  }
  else if (op == "loss") {
    losses++;
  }
  else if (op == "draw") {
    draws++;
  }
}

string Player::toString() const
{
  stringstream info;
  info << "Name: " << name << endl;
  info << "Wins: " << wins << endl;
  info << "Losses: " << losses << endl;
  info << "Draws: " << draws << endl;
  if (matches == 0) {
    info << "Win/Loss Ratio: N/A" << endl;
  } else {
    double ratio = (double(wins) / double(matches)) * 100.0;
    info << "Win/Loss Ratio: " << setprecision(0) << fixed << ratio << "%" << endl;
  }
  return info.str();
}

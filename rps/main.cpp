// Written by Aleks Christensen

// Test Cases
//
// Case 1
// Input: 2, John
// Output: ~~ Successfully added John to the roster ~~
//
// Case 2
// Input: 4
// Output: !! No players waiting for battle !!
//
// Case 3
//
// Input: 3, John
// Output: ~~ John added to next battle ~~

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <ctime>
#include "Player.h"
#define FIRST 0
#define SECOND 1

using namespace std;

int getInt(const int defaultValue = -1)
{
  string input;
  cin >> input;
  stringstream stream(input);
  int result = defaultValue;
  if (stream >> result) return result;
  else return result;
}

int findPlayer(string name, vector<Player*> players)
{
  for (size_t pos = 0; pos < players.size(); ++pos) {
    if ((*players.at(pos)).getName() == name) {
      return pos;
    }
  }
  return -1;
}

void listPlayers(vector<Player*> allPlayers)
{
  if (allPlayers.size() != 0) {
    cout << endl << "------------------------------" << endl;
    vector<Player*>::iterator player;
    for (player = allPlayers.begin(); player != allPlayers.end(); ++player) {
      cout << (*player)->toString();
      cout << "------------------------------" << endl;
    }
  }
  else {
    cout << endl << "!! No players !!" << endl;
  }
}

void listNext(vector<Player*> players)
{
  if (players.size() != 0) {
    vector<Player*>::iterator player;
    for (player = players.begin(); player != players.end(); ++player) {
      if (player == players.end() - 1) {
        cout << (*player)->getName() << endl;
      }
      else {
        cout << (*player)->getName() << ", ";
      }
    }
  }
  else {
    cout << endl << "!! No players waiting for battle !!" << endl;
  }
}

int addPlayer(vector<Player*>& allPlayers)
{
  cin.ignore();
  string name;
  cout << endl << "Please enter the new player's name: ";
  getline(cin, name);
  if (findPlayer(name, allPlayers) == -1) {
    Player* newPlayer = new Player(name);
    allPlayers.push_back(newPlayer);
    cout << endl << "~~ Successfully added " << name << " to player roster ~~" << endl;
    return 0;
  }
  else {
    cout << endl << "!! Player already in roster !!" << endl;
    return -1;
  }
}

int addNext(vector<Player*>& allPlayers, vector<Player*>& nextBattle)
{
  cin.ignore();
  string name;
  cout << endl << "Please enter the name of the player you want to add to the next battle: ";
  getline(cin, name);
  int loc = findPlayer(name, allPlayers);
  if (loc != -1) {
    Player* newContestant = allPlayers.at(loc);
    nextBattle.push_back(newContestant);
    cout << endl << "~~ " << name << " added to next battle ~~" << endl;
    return 0;
  }
  else {
    cout << endl << "!! Player not in roster !!" << endl;
    return -1;
  }
}

int getWinner(string throw1, string throw2)
{
  if (throw1 == throw2)  return 0;
  if (throw1 == "rock") {
    if (throw2 == "paper")  return 2;
    if (throw2 == "scissors")  return 1;
  }
  else if (throw1 == "paper") {
    if (throw2 == "scissors")  return 2;
    if (throw2 == "rock")  return 1;
  }
  else if (throw1 == "scissors") {
    if (throw2 == "rock")  return 2;
    if (throw2 == "paper")  return 1;
  }
  return -1;
}

int battle(vector<Player*>& nextBattle)
{
  while (nextBattle.size() >= 2) {
    Player* p1 = nextBattle.at(FIRST);
    Player* p2 = nextBattle.at(SECOND);
    string p1Name = p1->getName();
    string p2Name = p2->getName();
    string p1Throw = p1->getRPSThrow();
    string p2Throw = p2->getRPSThrow();
    cout << p1Name << " vs. " << p2Name << endl;
    if (p1Name == p2Name) {
      cout << endl << "This match is a draw because the two contestants are the same" << endl;
      p1->addRecord("draw");
      return 0;
    }
    cout << p1Name << " throws " << p1Throw << endl;
    cout << p2Name << " throws " << p2Throw << endl;
    int win = getWinner(p1Throw, p2Throw);
    if (win == 1) {
      cout << endl << p1Name << " wins!" << endl;
      p1->addRecord("win");
      p2->addRecord("loss");
    }
    else if (win == 2) {
      cout << endl << p2Name << " wins!" << endl;
      p1->addRecord("loss");
      p2->addRecord("win");
    }
    else if (win == 0) {
      cout << endl << "The match is a draw!" << endl;
      p1->addRecord("draw");
      p2->addRecord("draw");
    }
    nextBattle.erase(nextBattle.begin());
    nextBattle.erase(nextBattle.begin());
    return 0;
  }
  cout << endl << "!! Not enough players to begin battle !!" << endl;
  return 0;
}

int menu(vector<Player*>& allPlayers, vector<Player*>& nextBattle)
{
  srand(time(0));

  cout << endl;
  cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
  cout << "~~ Show all players [1]            ~~" << endl;
  cout << "~~ Add a player [2]                ~~" << endl;
  cout << "~~ Add to next battle [3]          ~~" << endl;
  cout << "~~ Show players in next battle [4] ~~" << endl;
  cout << "~~ Battle! [5]                     ~~" << endl;
  cout << "~~ Quit [6]                        ~~" << endl;
  cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
  cout << endl << "Choose an option: ";

  int opt = getInt();
  switch (opt) {
  case 1: // Show all players
    listPlayers(allPlayers);
    break;
  case 2: // Add player
    addPlayer(allPlayers);
    break;
  case 3: // Add to next battle
    addNext(allPlayers, nextBattle);
    break;
  case 4: // Show players in next battle
    listNext(nextBattle);
    break;
  case 5: // Battle
    battle(nextBattle);
    break;
  case 6: // Exit
    return opt;
    break;
  default:
    cout << endl << "!! Invalid Menu Option !!" << endl;
    break;
  }
}

int main()
{
  vector<Player*> allPlayers;
  vector<Player*> nextBattle;
  int opt;

  cout << "Rock, Paper, Scissors!" << endl;

  while (true) {
    opt = menu(allPlayers, nextBattle);
    if (opt == 6) {
      break;
    }
  }
  return 0;
}

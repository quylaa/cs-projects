// Written by Aleks Christensen
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <ctime>
#include "Player.h"

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

void doNothing()
{
  cout << endl << "?? This function is not yet implemented ??" << endl;
}

int menu(vector<Player*> allPlayers, vector<Player*> nextBattle)
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
      // listPlayers(allPlayers);
      doNothing();
      break;
    case 2: // Add player
      // addPlayer(allPlayers);
      doNothing();
      break;
    case 3: // Add to next battle
      // addNext(allPlayers, nextBattle);
      doNothing();
      break;
    case 4: // Show players in next battle
      // listNext(nextBattle);
      doNothing();
      break;
    case 5: // Battle
      // battle(nextBattle);
      doNothing();
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

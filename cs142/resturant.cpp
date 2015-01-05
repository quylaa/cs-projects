// Written by Aleks Christensen
//
// Test Cases
//
// Case 1:
// Input: 7
// Output: ?? Invalid Menu Option ??
//
// Case 2:
// Input: 2, Carl's Jr.
// Output: ~~ Added Carl's Jr. to restaurant list. ~~
//
// Case 3:
// Input: 3, Papa John's
// Output: ~~ Error: restaurant not in list. ~~

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <istream>
#include <sstream>
#include <cmath>
#include <cstdlib>
#include <ctime>

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

void init_restaurants(vector<string>& restaurants)
{
  restaurants.push_back("Taco Bell");
  restaurants.push_back("McDonald's");
  restaurants.push_back("Burger King");
  restaurants.push_back("The Onion");
  restaurants.push_back("Golden Corral");
  restaurants.push_back("Subway");
  restaurants.push_back("Olive Garden");
  restaurants.push_back("Red Robin");
}

int check_len(vector<string> restaurants)
{
  int len = restaurants.size();
  for (int p = 1; p <= 7; p++) {
    if (pow(2, p) == len) {
      return 0;
    }
  }
  return -1;
}

void shuffle(vector<string>& restaurants)
{
  size_t len = restaurants.size();
  string t;
  for (size_t p = 0; p < restaurants.size(); p++) {
    int place = rand() % len;
    if (place == p) {
      int place = rand() % len;
    }
    t = restaurants.at(p);
    restaurants.at(p) = restaurants.at(place);
    restaurants.at(place) = t;
  }

  cout << endl << "~~ List shuffled! ~~" << endl;
}

void print_restaurants(vector<string> restaurants)
{
  cout << endl;
  for (size_t t = 0; t < restaurants.size(); t++) {
    if (t == (restaurants.size() - 1)) {
      cout << restaurants.at(t) << endl;
    }
    else {
      cout << restaurants.at(t) << ", ";
    }
  }
}

int check_list(vector<string> restaurants, string to_check)
{
  for (size_t s = 0; s < restaurants.size(); s++) {
    if (to_check == restaurants.at(s)) {
      return s;
    }
  }
  return -1;
}

void change_list(vector<string>& restaurants, string op)
{
  cin.ignore();
  string place;
  cout << endl << "Please type the name of the restaurant: ";
  getline(cin, place);
  int test = check_list(restaurants, place);
  if (op == "add") {
    if (test == -1) {
      restaurants.push_back(place);
      cout << endl << "~~ Added " << place << " to restaurant list. ~~" << endl;
    }
    else {
      cout << endl << "~~ Error: restaurant already in list ~~" << endl;
    }
  }
  else if (op == "remove") {
    if (test != -1) {
      restaurants.erase(restaurants.begin()+test);
      cout << endl << "~~ Removed " << place << " from restaurant list. ~~" << endl;
    }
    else {
      cout << endl << "~~ Error: restaurant not in list ~~" << endl;
    }
  }
}

int find_rounds(int size){
  int rounds = 0;
  while (size > 1) {
    size /= 2;
    rounds ++;
  }
  return rounds;
}

void tournament(vector<string> restaurants)
{
  int total_rounds = find_rounds(restaurants.size());
  int current_round = 1;
  int current_match;
  cin.ignore();
  cout << endl << "!! THE BATTLE BEGINS !!" << endl;
  while (restaurants.size() > 1) {
    int rounds = restaurants.size() / 2;
    current_match = 1;
    for (int r = restaurants.size() - 1; r >= 0; r -= 2) {
      cout << endl << "!! Round " << current_round << " / " << total_rounds << ", Match " << current_match << " of " << rounds << " !!" << endl;
      string choice;
      cout << endl << "\t" << restaurants.at(r) << "\tvs.\t" << restaurants.at(r-1) << endl << endl;
      do {
        cout << "CHOOSE YOUR FAVORITE: ";
        getline(cin, choice);
        if (choice != restaurants.at(r) && choice != restaurants.at(r-1)) {
          cout << endl << "!! INVALID CHOICE. TRY AGAIN !!" << endl;
        }
      } while (choice != restaurants.at(r) && choice != restaurants.at(r-1));
      if (choice == restaurants.at(r)) {
        cout<< endl << "!! " << restaurants.at(r - 1) << " ELIMINATED !!" << endl;
        restaurants.erase(restaurants.begin() + (r - 1));
      }
      else {
        cout<< endl << "!! " << restaurants.at(r) << " ELIMINATED !!" << endl;
        restaurants.erase(restaurants.begin() + r);
      }
      current_match++;
    }
    current_round++;
  }
  cout << endl << endl << "!! WINNER: " << restaurants.at(0) << " !!" << endl << endl;
}

int menu(vector<string>& restaurants)
{
  cout << endl;
  cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
  cout << "~~ Display all restaurants [1]         ~~" << endl;
  cout << "~~ Add a restaurant [2]                ~~" << endl;
  cout << "~~ Remove a restaurant [3]             ~~" << endl;
  cout << "~~ Shuffle the list [4]               ~~" << endl;
  if (check_len(restaurants) != 0) {
    cout << "~~ Begin tournament (INVALID AMT) [5] ~~" << endl;
  } else {
    cout << "~~ Begin the tournament [5]           ~~" << endl;
  }
  cout << "~~ Quit the game [6]                  ~~" << endl;
  cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;

  cout << "Choose an option: ";
  int opt = getInt();

  switch (opt) {
  case 1:
    print_restaurants(restaurants);
    break;
  case 2:
    change_list(restaurants, "add");
    break;
  case 3:
    change_list(restaurants, "remove");
    break;
  case 4:
    shuffle(restaurants);
    break;
  case 5:
    if (check_len(restaurants) != 0) {
      cout << endl << "!! The number of restaurants must be a power of 2 !!" << endl;
    } else {
      tournament(restaurants);
    }
    break;
  case 6:
    return opt;
    break;
  default:
    cout << endl << "?? Invalid Menu Option ??" << endl;
    break;
  }
  return opt;
}

int main()
{
  srand(time(0));
  vector<string> restaurants;
  init_restaurants(restaurants);
  cout << endl << "!! Welcome to restaurant Rodeo !!" << endl << endl;
  while (true) {
    int i = menu(restaurants);
    if (i == 6) { break; }
  }
  return 0;
}

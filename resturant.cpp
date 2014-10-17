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
// Output: ~~ Added Carl's Jr. to resturant list. ~~
//
// Case 3:
// Input: 3, Papa John's
// Output: ~~ Error: Resturant not in list. ~~

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

void init_resturants(vector<string>& resturants)
{
	resturants.push_back("Taco Bell");
	resturants.push_back("McDonald's");
	resturants.push_back("Burger King");
	resturants.push_back("The Onion");
	resturants.push_back("Golden Corral");
	resturants.push_back("Subway");
	resturants.push_back("Olive Garden");
	resturants.push_back("Red Robin");
}

int check_len(vector<string> resturants)
{
	int len = resturants.size();
	for (int p = 1; p <= 7; p++) {
		if (pow(2, p) == len) {
			return 0;
		}
	}
	return -1;
}

void shuffle(vector<string>& resturants)
{
	size_t len = resturants.size();
	string t;
	for (size_t p = 0; p < resturants.size(); p++) {
		int place = rand() % len;
		if (place == p) {
			int place = rand() % len;
		}
		t = resturants.at(p);
		resturants.at(p) = resturants.at(place);
		resturants.at(place) = t;
	}

	cout << endl << "~~ List shuffled! ~~" << endl;
}

void print_resturants(vector<string> resturants)
{
	cout << endl;
	for (size_t t = 0; t < resturants.size(); t++) {
		if (t == (resturants.size() - 1)) {
			cout << resturants.at(t) << endl;
		}
		else {
			cout << resturants.at(t) << ", ";
		}
	}
}

int check_list(vector<string> resturants, string to_check)
{
	for (size_t s = 0; s < resturants.size(); s++) {
		if (to_check == resturants.at(s)) {
			return s;
		}
	}
	return -1;
}

void change_list(vector<string>& resturants, string op)
{
	cin.ignore();
	string place;
	cout << endl << "Please type the name of the resturant: ";
	getline(cin, place);
	int test = check_list(resturants, place);
	if (op == "add") {
		if (test == -1) {
			resturants.push_back(place);
			cout << endl << "~~ Added " << place << " to resturant list. ~~" << endl;
		}
		else {
			cout << endl << "~~ Error: Resturant already in list ~~" << endl;
		}
	}
	else if (op == "remove") {
		if (test != -1) {
			resturants.erase(resturants.begin()+test);
			cout << endl << "~~ Removed " << place << " from resturant list. ~~" << endl;
		}
		else {
			cout << endl << "~~ Error: Resturant not in list ~~" << endl;
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

void tournament(vector<string> resturants)
{
	int total_rounds = find_rounds(resturants.size());
	int current_round = 1;
	int current_match;
	cin.ignore();
	cout << endl << "!! THE BATTLE BEGINS !!" << endl;
	while (resturants.size() > 1) {
		int rounds = resturants.size() / 2;
		current_match = 1;
		for (int r = resturants.size() - 1; r >= 0; r -= 2) {
			cout << endl << "!! Round " << current_round << " / " << total_rounds << ", Match " << current_match << " of " << rounds << " !!" << endl;
			string choice;
			cout << endl << "\t" << resturants.at(r) << "\tvs.\t" << resturants.at(r-1) << endl << endl;
			do {
				cout << "CHOOSE YOUR FAVORITE: ";
				getline(cin, choice);
				if (choice != resturants.at(r) && choice != resturants.at(r-1)) {
					cout << endl << "!! INVALID CHOICE. TRY AGAIN !!" << endl;
				}
			} while (choice != resturants.at(r) && choice != resturants.at(r-1));
			if (choice == resturants.at(r)) {
				cout<< endl << "!! " << resturants.at(r - 1) << " ELIMINATED !!" << endl;
				resturants.erase(resturants.begin() + (r - 1));
			}
			else {
				cout<< endl << "!! " << resturants.at(r) << " ELIMINATED !!" << endl;
				resturants.erase(resturants.begin() + r);
			}
			current_match++;
		}
		current_round++;
	}
	cout << endl << endl << "!! WINNER: " << resturants.at(0) << " !!" << endl << endl;
}

int menu(vector<string>& resturants)
{
	cout << endl;
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	cout << "~~ Display all resturants [1]         ~~" << endl;
	cout << "~~ Add a resturant [2]                ~~" << endl;
	cout << "~~ Remove a resturant [3]             ~~" << endl;
	cout << "~~ Shuffle the list [4]               ~~" << endl;
	if (check_len(resturants) != 0) {
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
		print_resturants(resturants);
		break;
	case 2:
		change_list(resturants, "add");
		break;
	case 3:
		change_list(resturants, "remove");
		break;
	case 4:
		shuffle(resturants);
		break;
	case 5:
		if (check_len(resturants) != 0) {
			cout << endl << "!! The number of resturants must be a power of 2 !!" << endl;
		} else {
			tournament(resturants);
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
	vector<string> resturants;
	init_resturants(resturants);
	cout << endl << "!! Welcome to Resturant Rodeo !!" << endl << endl;
	while (true) {
		int i = menu(resturants);
		if (i == 6) { break; }
	}
	return 0;
}

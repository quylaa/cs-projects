#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <istream>
#include <algorithm>
#include <cmath>

using namespace std;

void do_nothing()
{
	cout << endl << "?? This function is not yet implemented ??" << endl;
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
	random_shuffle(resturants.begin(), resturants.end());
	cout << endl << "~~ List shuffled! ~~" << endl;
}

void print_resturants(vector<string> resturants)
{
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

void tournament(vector<string> resturants)
{
	cin.ignore();
	cout << endl << "!! THE BATTLE BEGINS !!" << endl;
	while (resturants.size() > 1) {
		int rounds = resturants.size() / 2;
		for (int r = resturants.size() - 1; r >= 0; r -= 2) {
			string choice;
			cout << endl << "\t" << resturants.at(r) << "\tvs.\t" << resturants.at(r-1) << endl;
			do {
				cout << "MAKE YOUR CHOICE: ";
				getline(cin, choice);
				if (choice != resturants.at(r) && choice != resturants.at(r-1)) {
					cout << endl << "INCORRECT CHOICE. TRY AGAIN" << endl;
				}
			} while (choice != resturants.at(r) && choice != resturants.at(r-1));
			if (choice == resturants.at(r)) {
				resturants.erase(resturants.begin() + r);
			}	else {
				resturants.erase(resturants.begin() + (r - 1));
			}
			cout<< endl << "!! " << choice << " ELIMINATED !!" << endl;
		}
	}
	cout << endl  << endl << "!! WINNER: " << resturants.at(0) << " !!" << endl << endl;
}

int menu(vector<string>& resturants)
{
	int opt;
	string place;

	cout << endl << "!! Welcome to Resturant Rodeo !!" << endl << endl;
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
	cin >> opt;
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
		do_nothing();
		break;
	}
	return opt;
}

int main()
{
	vector<string> resturants;
	init_resturants(resturants);
	while (true) {
		int i = menu(resturants);
		if (i == 6) { break; }
	}
	return 0;
}

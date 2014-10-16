#include <iostream>
#include <iomanip>
#include <vector>
#include <string>

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
			if (s == 0) {
				return -1;
			}
			return s;
		}
	}
	return 0;
}

void change_list(vector<string>& resturants, string new_place, string op)
{
	if (op == "add") {
		int test = check_list(resturants, new_place);
		if (test == 0) {
			resturants.push_back(new_place);
			cout << endl << "~~ Added " << new_place << " to resturant list. ~~" << endl;
		}
		else {
			cout << endl << "~~ Error: Resturant already in list ~~" << endl;
		}
	}
	else if (op == "remove") {
		int test = check_list(resturants, new_place);
		if (test != 1) {
			resturants.erase(resturants.begin()+test);
			cout << endl << "~~ Removed " << new_place << " from resturant list. ~~" << endl;
		}
		else if (test == -1) {
			resturants.erase(resturants.begin());
			cout << endl << "~~ Removed " << new_place << " from resturant list. ~~" << endl;
		}
		else {
			cout << endl << "~~ Error: Resturant not in list ~~" << endl;
		}
	}
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
	cout << "~~ Begin the tournament [5]           ~~" << endl;
	cout << "~~ Quit the game [6]                  ~~" << endl;
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;

	cout << "Choose an option: ";
	cin >> opt;
	switch (opt) {
	case 1:
		print_resturants(resturants);
		break;
	case 2:
		cout << endl << "Please type the name of the resturant you want to add: ";
		cin >> place;
		change_list(resturants, place, "add");
		break;
	case 3:
		cout << endl << "Please type the name of the resturant you want to remove: ";
		cin >> place;
		change_list(resturants, place, "remove");
		break;
	case 4:
		do_nothing();
		break;
	case 5:
		do_nothing();
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
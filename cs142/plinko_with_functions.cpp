// Written by Aleks Christensen

// Test cases
// 
// Case 1:
//   Input: 7
//   Output: ~~ Invalid menu choice ~~
//
// Case 2:
//   Input: 1, -1
//   Output: ~~ Invalid slot ~~
//
// Case 3:
//   Input: 2, 3, 6
//   Output: ~~ Dropping 3 chips into slot 6 ~~
//
//         ~~You won $1500!~~
//
//         ~~Amount earned per chip(average) : $500 ~~

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <string>
using namespace std;

int lr()
{
	double r = (rand() * 1.0) / RAND_MAX;
	int s = r + 0.5;
	return s;
}

void reset_path(double path[])
{
	int PATH_SIZE = 13;
	for (int j = 0; j < PATH_SIZE; j++) {
		path[j] = 0.0;
	}
}

double step(double pos)
{
	int dir = lr();
	if (pos == 0.0) {
		pos += 0.5;
	}
	else if (pos == 8.0) {
		pos -= 0.5;
	}
	else if (dir == 0) {
		pos -= 0.5;
	}
	else if (dir == 1) {
		pos += 0.5;
	}
	return pos;
}

void single(int slot, double path[])
{
	int PATH_SIZE = 13;
	reset_path(path);
	path[0] = slot;
	double pos = slot;
	for (int d = 1; d < PATH_SIZE; d++) {
		pos = step(pos);
		path[d] = pos;
	}
}

void sum_money(double path[], int SLOT_VALUES[], int &money)
{
	int FINAL_STEP = 12;
	int last = path[FINAL_STEP];
	money += SLOT_VALUES[last];
}

void many(int chips, int slot, int &money, double path[], int SLOT_VALUES[])
{
	for (int a = 1; a <= chips; a++) {
		reset_path(path);
		single(slot, path);
		sum_money(path, SLOT_VALUES, money);
	}
}

void multi(int chips, int &money, double path[], int SLOT_VALUES[], int multi_slots[], int multi_avgs[])
{
	int MULTI_SIZE = 9;
	for (int b = 0; b<MULTI_SIZE; b++) {
		money = 0;
		many(chips, b, money, path, SLOT_VALUES);
		multi_slots[b] = money;
		multi_avgs[b] = money / chips;
	}
}

void print(double path[], int money, int chips, int option, int multi_slots[], int multi_avgs[])
{
	int PATH_SIZE = 13;
	int MULTI_SIZE = 9;

	switch (option) {
		case 1:
			cout << "[";
			for (int m = 0; m<PATH_SIZE; m++) {
				cout << path[m] << " ";
			}
			cout << "\b]" << endl;
			cout << "~~ You won $" << money << "!~~" << endl;
			break;
		case 2:
			cout << endl << "~~ You won $" << money << "!~~" << endl;
			cout << endl << "~~ Amount earned per chip (average): $" << money / chips << " ~~" << endl;
			break;
		case 3:
			cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
			cout << endl << "~~ Slot\t\tMoney Earned\tMoney/Chip (avg)     ~~";
			for (int c = 0; c<MULTI_SIZE; c++) {
				cout << endl << "~~ " << c << "\t\t$" << multi_slots[c] << "\t\t$" << multi_avgs[c] << "\t\t     ~~";
			}
			cout << endl << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
			break;
	}
}

void invalid(int error)
{
	int INVALID_SLOT = 1;
	int INVALID_CHIPS = 2;
	int INVALID_MENU = 3;

	if (error == INVALID_SLOT) {
		cout << endl << "~~ Invalid slot ~~" << endl;
	}
	if (error == INVALID_CHIPS) {
		cout << endl << "~~ Invalid number of chips ~~" << endl;
	}
	if (error == INVALID_MENU) {
		cout << endl << "~~ Invalid menu choice ~~" << endl;
	}
}

int slot_check(int slot)
{
	if (slot < 0 || slot > 8) {
		return 1;
	}
	else {
		return 0;
	}
}

int getInt(const int defaultValue = -1)
{
	string input;
	cin >> input;
	stringstream stream(input);
	int result = defaultValue;
	if (stream >> result) return result;
	else return result;
}

int main()
{
	srand(time(0));
	int money;
	int chips;
	int slot;
	int multi_avgs[9];
	int multi_slots[9];
	double path[13];

	int SLOT_VALUES[9] = { 100, 500, 1000, 0, 10000, 0, 1000, 500, 100 };
	int INVALID_SLOT = 1;
	int INVALID_CHIPS = 2;
	int INVALID_MENU = 3;

	while (true) {
		cout << endl << "~~ Welcome to Plinko! ~~" << endl;
		cout << "//----------------------------------------//" << endl;
		cout << "// Drop one chip into a slot [1]          //" << endl;
		cout << "// Drop multiple chips in a slot [2]      //" << endl;
		cout << "// Drop multiple chips into all slots [3] //" << endl;
		cout << "// Exit [4]                               //" << endl;
		cout << "//----------------------------------------//" << endl;
		cout << endl << "Make a choice: ";
		int sel = getInt();
		switch (sel) {
			case 1:
				cout << "Choose a slot to drop it in [0-8]: ";
				cin >> slot;
				if (slot_check(slot) == 1) {
					invalid(INVALID_SLOT);
					break;
				}
				cout << endl << "~~ Dropping a chip into slot " << slot << " ~~" << endl;
				money = 0;
				single(slot, path);
				sum_money(path, SLOT_VALUES, money);
				print(path, money, 0, 1, multi_slots, multi_avgs);
				break;
			case 2:
				cout << "How many chips do you want to drop? ";
				cin >> chips;
				if (chips < 1) {
					invalid(INVALID_CHIPS);
					break;
				}
				cout << "Choose a slot to drop them in [0-8]: ";
				cin >> slot;
				if (slot_check(slot) == 1) {
					invalid(INVALID_SLOT);
					break;
				}
				cout << endl << "~~ Dropping " << chips << " chips into slot " << slot << " ~~" << endl;
				money = 0;
				many(chips, slot, money, path, SLOT_VALUES);
				print(path, money, chips, 2, multi_slots, multi_avgs);
				break;
			case 3:
				cout << "How many chips do you want to drop? ";
				cin >> chips;
				if (chips < 1) {
					invalid(INVALID_CHIPS);
					break;
				}
				cout << endl << "~~ Dropping " << chips << " chips into every slot ~~" << endl;
				multi(chips, money, path, SLOT_VALUES, multi_slots, multi_avgs);
				print(path, money, chips, 3, multi_slots, multi_avgs);
				break;
			case 4:
				cout << endl << "~~ Exiting game... ~~" << endl;
				return 0;
				break;
			default:
				invalid(INVALID_MENU);
				break;
		}
	}
	return 0;
}
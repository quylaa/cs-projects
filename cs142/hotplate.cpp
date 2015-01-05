#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
using namespace std;

const int ROWS = 20;
const int COLUMNS = 20;
const int FIRST = 0;
const int LAST = 19;

void init_plate(double plate[][20])
{
	int row, col;
	for ( row=0; row<ROWS; row++ ) {
		if ( row == FIRST || row == LAST ) {
			for (col = 0; col < COLUMNS; col++) {
				plate[row][col] = 100.0;
			}
			plate[row][FIRST] = 0.0;
			plate[row][LAST] = 0.0;
		}
		else {
			for ( col=0; col<COLUMNS; col++ ) {
				plate[row][col] = 0.0;
			}
		}
	}
}

double avg_temp(double t1, double t2, double t3, double t4)
{
	double all = 4.0;
	return (t1 + t2 + t3 + t4) / all;
}

double update(double plate[][20], double new_plate[][20])
{
	double change = 0.0;
	for (int row = 0; row < ROWS; row++) {
		if (row == FIRST || row == LAST) {
			for (int col = 0; col < COLUMNS; col++) {
				if (col == FIRST || col == LAST) {
					plate[row][col] = 0.0;
				}
				else {
					plate[row][col] = 100.0;
				}
			}
		}
		else {
			for (int col = 0; col < COLUMNS; col++) {
				if (col == FIRST || col == LAST) {
					plate[row][col] = 0.0;
				}
				else {
					double old = plate[row][col];
					plate[row][col] = avg_temp(plate[row][col - 1], plate[row - 1][col], plate[row][col + 1], plate[row + 1][col]);
					double diff = plate[row][col] - old;
					if (diff > change) { change = diff; }
				}
			}
		}
	}
	return change;
}

double run_plate(double plate[][20])
{
	double new_plate[20][20];
	double change = update(plate, new_plate);
	return change;
}

void print_plate(double plate[][20])
{
	for (int row = 0; row<ROWS; row++) {
		for (int col = 0; col<COLUMNS; col++) {
			cout << setw(2) << setprecision(1) << fixed << plate[row][col] << " ";
		}
		cout << endl;
	}
	cout << "------------------------------------------------------------" << endl;
}

void write_out(double plate[][20])
{
	ofstream file;
	file.open("hot_plate_temps.csv");
	for (int row = 0; row < ROWS; row++) {
		for (int col = 0; col < COLUMNS; col++) {
			if (col == LAST) { file << plate[row][col] << endl; }
			else { file << plate[row][col] << ","; }
		}
	}
	file.close();
}

int main()
{
	double plate[20][20];
	double change;
	double min_change = 0.1;
	init_plate(plate);
	print_plate(plate);
	do {
		change = run_plate(plate);
	} while (change > min_change);
	print_plate(plate);
	write_out(plate);
	cout << "CSV file written to your desktop." << endl;
	system("pause");
	return 0;
}

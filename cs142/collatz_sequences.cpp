#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <iomanip>
using namespace std;

const int SEQ_INDEX = 0;
const int ODD_INDEX = 1;
const int HIGH_INDEX = 2;
const int AVG_ODD_INDEX = 0;
const int AVG_HIGH_INDEX = 1;
const int MOST_INDEX = 1;
const int COLUMN_WIDTH_HIGHEST = 14;
const int COLUMN_WIDTH_ODDS = 22;
const string DIVIDER = "-------------------------------------";
const int INPUT = 1;

int highest_count[2] = { 0, 0 };
int most_odd[2] = { 0, 0 };

vector<int> sequence(int num)
{
	vector<int> path;
	path.push_back(num);
	int temp;
	while (num > 1) {
		temp = num % 2;
		if (temp == 0) {
			num /= 2;
			path.push_back(num);
		}
		else {
			num = (num * 3) + 1;
			path.push_back(num);
		}
	}
	return path;
}

int num_odd(vector<int> seq)
{
	int count = 0;
	for (size_t m = 0; m < seq.size(); m++) {
		if (seq.at(m) % 2 != 0) {
			count++;
		}
	}
	return count;
}

int highest(vector<int> seq)
{
	sort(seq.begin(), seq.end());
	return seq.back();
}

void collatz(int start, int stop, int range, vector<vector<int>>& seqs)
{
	int seq_num = range;
	vector<int> seq;
	for (int n = start; n <= stop; n++) {
		seq = sequence(n);
		int cur_seq = range - seq_num;
		seq_num -= 1;
		int odd = num_odd(seq);
		int high = highest(seq);
		seqs.at(cur_seq).at(ODD_INDEX) = odd;
		seqs.at(cur_seq).at(HIGH_INDEX) = high;
		if (odd >= most_odd[MOST_INDEX]) {
			most_odd[MOST_INDEX] = odd;
			most_odd[SEQ_INDEX] = n;
		}
		if (high >= highest_count[MOST_INDEX]) {
			highest_count[MOST_INDEX] = high;
			highest_count[SEQ_INDEX] = n;
		}
		cout << "[";
		for (size_t p = 0; p < seq.size(); p++) {
			cout << seq.at(p) << ", ";
		}
		cout << "\b\b] " << endl;
		cout.width(COLUMN_WIDTH_HIGHEST); cout << right << seqs.at(cur_seq).at(HIGH_INDEX);
		cout.width(COLUMN_WIDTH_ODDS); cout << right << seqs.at(cur_seq).at(ODD_INDEX);
		cout << endl << DIVIDER << endl;
	}
}

void avgs(vector<vector<int>> seqs, double avg[])
{
	double highs = 0.0;
	double odds = 0.0;
	int seq_size = seqs.size();
	for (size_t b = 0; b < seqs.size(); b++) {
		highs += seqs.at(b).at(HIGH_INDEX);
		odds += seqs.at(b).at(ODD_INDEX);
	}
	double avg_high = highs / seq_size;
	double avg_odd = odds / seq_size;
	avg[AVG_HIGH_INDEX] = avg_high;
	avg[AVG_ODD_INDEX] = avg_odd;
}

void invalid(int error)
{
	if (error == INPUT) {
		cout << endl << "-- Invalid input --" << endl;
	}
}

void init_vector(int start, int stop, vector<vector<int>>& seqs)
{
	int c = 0;
	while (start <= stop) {
		seqs.at(c).at(SEQ_INDEX) = start;
		start++;
		c++;
	}
}

int main()
{
	int start, stop;
	while (true) {
		cout << endl << "~~ Collatz Conjecture ~~" << endl;
		cout << "What number should the sequences start at? [1<]";
		cin >> start;
		if (!(start > 1)) {
			invalid(INPUT);
			continue;
		}
		cout << "Now what number should it stop at? ";
		cin >> stop;
		if (!(stop >= start)) {
			invalid(INPUT);
			continue;
		}
		else {
			int range = (stop - start) + 1;
			vector< vector<int> > seqs(range, vector<int>(3));
			init_vector(start, stop, seqs);
			cout << "Sequence range " << start << " to " << stop << endl;
			cout << "Highest number\tAmount of Odd Numbers" << endl;
			cout << DIVIDER << endl;
			collatz(start, stop, range, seqs);
			double avg[2] = { 0, 0 };
			avgs(seqs, avg);
			cout << endl << "Highest number: " << highest_count[MOST_INDEX] << " in sequence " << highest_count[SEQ_INDEX] << endl;
			cout << "Most odd numbers: " << most_odd[MOST_INDEX] << " in sequence " << most_odd[SEQ_INDEX] << endl;
			cout << "Average highest number: " << setprecision(2) << fixed << avg[AVG_HIGH_INDEX] << endl;
			cout << "Average amount of odd numbers: " << setprecision(2) << fixed << avg[AVG_ODD_INDEX] << endl;
			break;
		}
	}
	system("pause");
	return 0;
}
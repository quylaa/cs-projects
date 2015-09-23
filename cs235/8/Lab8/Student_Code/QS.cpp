// Written by Aleks Christensen

#include "QS.h"
#include <cmath>
#include <sstream>
#include <math.h>

void QS::sortAll()
{
	if (Array == NULL) return;

	recursiveSort(0, currentSize-1);
}

void QS::recursiveSort(int left, int right)
{
	if (right-left > 1)	{
		int middle = medianOfThree(left, right);
		int midpart = partition(left, right, middle);
		recursiveSort(left, midpart-1);
		recursiveSort(midpart+1, right);
	}

	return;
}

int QS::medianOfThree(int left, int right)
{
	if ((left < 0) || (right < 0) || (Array == NULL) || (!(left < right)) || (left >= currentSize) || (right >= currentSize)) return -1;
	int mid = (left + right) / 2;

	if (Array[mid] < Array[left]) {
		Swap(left, mid);
	}

	if (Array[right] < Array[mid]) {
		Swap(mid, right);
	}

	if (Array[mid] < Array[left]) {
		Swap(left, mid);
	}

	return mid;
}


int QS::partition(int left, int right, int pIndex)
{

	if ((left < 0) || (right < 0) ||(Array == NULL)|| (!(left < right)) || (left >= currentSize) || (right >= currentSize) || (!(pIndex > left && pIndex < right))) return -1;

	Swap(right, pIndex);

	int up = left;
	int down = right - 1;

	do {
		while (up < down && up < right - 1 && Array[up] < Array[right])	++up;

		while (down > up && down > left && Array[down] > Array[right]) --down;

		if (up < down) {
			if(Array[up] > Array[down]) {
				Swap(up, down);
			}
		}
	} while (up < down);

	if (up == right) return right - 1;
	Swap(right, up);

	return up;
}

string QS::getArray()
{
	stringstream ss;
	for (int i = 0; i < currentSize; i++) {
		ss << Array[i];

		if (i != currentSize-1)	{
			ss << ",";
		}
	}
	return ss.str();
}

int QS::getSize()
{
	return currentSize;
}

void QS::addToArray(int value)
{
	if (capacity == 0) {
		return;
	}

	Array[currentSize] = value;
	currentSize++;
}

bool QS::createArray(int size)
{
	capacity = size;

	if (size > 0) {
		Array = new int[size];
		return true;
	}

	return false;
}

void QS::clear()
{
	delete[] Array;
	Array = NULL;
	capacity = 0;
	currentSize = 0;
}






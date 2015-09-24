// Writte by Aleks Christensen

#ifndef QS_H_
#define QS_H_

#pragma once
#include <iostream>
#include <string>
#include "QSInterface.h"

using namespace std;

class QS : public QSInterface
{
private:
	int*Array = NULL;
	int currentSize = 0;
	int capacity = 0;
	int left = 0;
	int right = 0;

public:
	QS() {int*Array = NULL;}
	~QS(){clear();}

	int pivotIndex;

	void sortAll();

	int medianOfThree(int left, int right);

	int partition(int left, int right, int pivotIndex);

	string getArray();

	int getSize();

	void addToArray(int value);

	bool createArray(int size);

	void recursiveSort (int left, int right);

	void clear();

	void Swap(int one, int two)
	{
		int temp = Array[one];
		Array[one] = Array[two];
		Array[two] = temp;
	}
};




#endif

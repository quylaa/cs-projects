/*
 * QSInterface.h
 *
 *  Created on: May 1, 2014
 *      Author: seamane
 */

#ifndef QSINTERFACE_H_
#define QSINTERFACE_H_

#pragma once
#include <iostream>
#include <string>
using namespace std;

/*
 * WARNING: It is expressly forbidden to modify any part of this document, including its name
 */

class QSInterface
{
	public:
		QSInterface(){}
		virtual ~QSInterface(){}

		/*
		 * sortAll()
		 *
		 * Sorts elements of the array.  After this method is called, every
		 * element in the array is less than or equal to the following element.
		 *
		 * Does nothing if the array is empty.
		 */
		virtual void sortAll() = 0;

		/*
		 * medianOfThree()
		 *
		 * Performs median-of-three pivot selection from among the values in
		 * the array between the two given indices. Median-of-three pivot
		 * selection will sort the first, middle, and last elements in a given
		 * array with respect to each other. After this method is called,
		 * data[first] <= data[middle] <= data[last], where middle =
		 * (first + last)/2. The middle index will be the pivot value returned.
		 *
		 * Returns -1 if the array is empty, if either of the given integers
		 * is out of bounds, or if the first integer is not less than the second
		 * integer.
		 *
		 * @param left
		 * 		the left boundary for the subarray from which to find a pivot
		 * @param right
		 * 		the right boundary for the subarray from which to find a pivot
		 * @return
		 *		the index of the pivot; -1 if provided with invalid input
		 */
		virtual int medianOfThree(int left, int right) = 0;

		/*
		 * Partitions a subarray around a pivot value selected according to
		 * median-of-three pivot selection.
		 *
		 * The values which are smaller than the pivot should be placed to the left
		 * of the pivot; the values which are larger than the pivot should be placed
		 * to the right of the pivot.
		 *
		 * Returns -1 if the array is null, if either of the given integers is out of 			
		 * bounds, or if the first integer is not less than the second integer, or if the 			 
		 * pivot is not between the two boundaries.
		 *
		 * @param left
		 * 		the left boundary for the subarray to partition
		 * @param right
		 * 		the right boundary for the subarray to partition
		 * @param pivotIndex
		 * 		the index of the pivot in the subarray
		 * @return
		 *		the pivot's ending index after the partition completes; -1 if
		 * 		provided with bad input
		 */
		virtual int partition(int left, int right, int pivotIndex) = 0;

		/*
		 * Gets the array of values and puts them into a string. For example: if my array 			 
		 * looked like {5,7,2,9,0}, then the string to be returned would look like "5,7,2,9,0" 			 
		 * with no trailing comma.
		 *
		 * Returns null, if the array is null or empty.
		 *
		 * @return
		 *		the string representation of the current array
		 */
		virtual string getArray() = 0;

		/*
		 * Gets the size of the current array.
		 *
		 * @return
		 * 		the current size
		 */
		virtual int getSize() = 0;

		/*
		 * Adds the given value to the array.
		 */
		virtual void addToArray(int value) = 0;

		/*
		 * Creates an array with the given size.
		 *
		 * Returns false if the given value is non-positive, true otherwise.
		 *
		 * @param
		 *		size of array
		 * @return
		 *		true if the array was created, false otherwise
		 */
		virtual bool createArray(int size) = 0;

		/*
		 * Clears the array.
		 */
		virtual void clear() = 0;
};



#endif /* QSINTERFACE_H_ */

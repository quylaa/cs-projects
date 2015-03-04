#include "Factory.h"

//You may add #include statements here
#include "List.h"
/*
	You will MODIFY THIS DOCUMENT.
*/
//=======================================================================================
/*
	getLinkedListInt() and

	Creates and returns an object whose class extends LinkedListInterface.
	This should be an object of a class you have created.

	Example: If you made a class called "LinkedList", you might say, "return new LinkedList<int>();".
*/
LinkedListInterface<int> * Factory::getLinkedListInt()
{
	return new List<int>();//Modify this line
}

/*
	getLinkedListString() and

	Creates and returns an object whose class extends LinkedListInterface.
	This should be an object of a class you have created.

	Example: If you made a class called "LinkedList", you might say, "return new LinkedList<string>();".
*/
LinkedListInterface<string>* Factory::getLinkedListString()
{
	return new List<string>;//Modify this line
}

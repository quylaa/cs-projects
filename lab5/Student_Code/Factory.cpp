#include "Factory.h"
//You may add #include statments here
#include "Path.h"

using namespace std;

/*
	Unlike all other documents provided, you may modify this document slightly (but do not change its name)
*/
//=======================================================================================
/*
	createPathfinder()

	Creates and returns an object whose class extends PathfinderInterface.
	This should be an object of a class you have created.

	Example: If you made a class called "Pathfinder", you might say, "return new Pathfinder();".
*/
PathfinderInterface* Factory::createPathfinder()
{
	return new Path();//Modify this line
}
//=======================================================================================

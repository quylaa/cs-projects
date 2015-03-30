// Written by Aleks Christensen

#include "StationInterfaceExtra.h"
#include "MyStack.h"
#include "MyQueue.h"
#include "MyDeque.h"
#include "ORDeque.h"
#include "IRDeque.h"

class Station : public StationInterfaceExtra
{
	private:
		MyStack* stak = new MyStack(); // Stack structure
		MyQueue* que = new MyQueue(); // Queue structure
		MyDeque* deq = new MyDeque(); // Deque structure
		IRDeque* ird = new IRDeque(); // Input-restricted structure
		ORDeque* ord = new ORDeque(); // Output-restricted structure

		int currentCar; // ID of the current car

		// Constants
		const int SIZE = 5;

	public:
			Station();
			~Station();

			/**
			 * Check if giver car's id is in any structure
			 *
			 * @param car the ID of the car to check for
			 * @return true if the ID is not found in any structure; false otherwise
			 */
			bool checkId(int car);

			// Part 1

			/**
			 * Let another car arrive at the station and become the current car.
		 	 * Do not allow a new car to arrive if any of the following conditions apply:
		 	 * 1.	There is already a current car
		 	 * 2.	The new car's ID already exists in any structure
		 	 * 3.	The new car's ID is negative
		 	 *
		 	 * @param car the ID of the car arriving at the station
		 	 * @return true if the car successfully arrived; false otherwise
		 	 */
		 	bool addToStation(int car);

		 	/**
		 	 * Returns the ID of the current car.
		 	 * Return -1 if there is no current car.
		 	 *
		 	 * @return the ID of the current car; -1 if there is no current car
		 	 */
		 	int showCurrentCar();

			/**
		 	 * Removes the current car from the station.
		 	 * Does nothing if there is no current car.
		 	 *
		 	 * @return true if the current car successfully left; false otherwise
		 	 */
		 	 bool removeFromStation();

			//Part 2--------------------------------------------------------------
			/**
			 * Adds the current car to the stack.  After this operation, there should be no current car.
			 * Does nothing if there is no current car or if the stack is already full.
			 *
			 * @return true if the car is successfully added to the stack; false otherwise
			 */
			bool addToStack();
	
			/**
			 * Removes the first car in the stack and makes it the current car.
			 * Does nothing if there is already a current car or if the stack already empty.
			 *
			 * @return true if the car is successfully removed from the stack; false otherwise
			 */
			bool removeFromStack();
	
			/**
			 * Returns the ID of the first car in the stack.
			 *
			 * @return the ID of the first car in the stack; -1 if the stack is empty
			 */
			int showTopOfStack();
	
			/**
			 * Returns the number of cars in the stack.
			 *
			 * @return the number of cars in the stack
			 */
			int showSizeOfStack();
	
			//Part 3--------------------------------------------------------------
			/**
			 * Adds the current car to the queue.  After this operation, there should be no current car.
			 * Does nothing if there is no current car or if the queue is already full.
			 *
			 * @return true if the car is successfully added to the queue; false otherwise
			 */
			bool addToQueue();
	
			/**
			 * Removes the first car in the queue and makes it the current car.
			 * Does nothing if there is already a current car or if the queue already empty.
			 *
			 * @return true if the car is successfully removed from the queue; false otherwise
			 */
			bool removeFromQueue();
	
			/**
			 * Returns the ID of the first car in the queue.
			 *
			 * @return the ID of the first car in the queue; -1 if the queue is empty
			 */
			int showTopOfQueue();
	
			/**
			 * Returns the number of cars in the queue.
			 *
			 * @return the number of cars in the queue
			 */
			int showSizeOfQueue();
	
			//Part 4--------------------------------------------------------------
			/**
			 * Adds the current car to the deque on the left side.  After this operation, there should be no current car.
			 * Does nothing if there is no current car or if the deque is already full.
			 *
			 * @return true if the car is successfully added to the deque; false otherwise
			 */
			bool addToDequeLeft();
	
			/**
			 * Adds the current car to the deque on the right side.  After this operation, there should be no current car.
			 * Does nothing if there is no current car or if the deque is already full.
			 *
			 * @return true if the car is successfully added to the deque; false otherwise
			 */
			bool addToDequeRight();
	
			/**
			 * Removes the leftmost car in the deque and makes it the current car.
			 * Does nothing if there is already a current car or if the deque already empty.
			 *
			 * @return true if the car is successfully removed from the deque; false otherwise
			 */
			bool removeFromDequeLeft();
	
			/**
			 * Removes the rightmost car in the deque and makes it the current car.
			 * Does nothing if there is already a current car or if the deque already empty.
			 *
			 * @return true if the car is successfully removed from the deque; false otherwise
			 */
			bool removeFromDequeRight();
	
			/**
			 * Returns the ID of the leftmost car in the deque.
			 *
			 * @return the ID of the leftmost car in the deque; -1 if the deque is empty
			 */
			int showTopOfDequeLeft();
	
			/**
			 * Returns the ID of the rightmost car in the deque.
			 *
			 * @return the ID of the rightmost car in the deque; -1 if the deque is empty
			 */
			int showTopOfDequeRight();
	
			/**
			 * Returns the number of cars in the deque.
			 *
			 * @return the number of cars in the deque
			 */
			int showSizeOfDeque();

			//Input-Restricted Deque----------------------------------------------
			/**
			 * Adds the current car to the IRDeque on the left side.  After this operation, there should be no current car.
			 * Does nothing if there is no current car or if the IRDeque is already full.
			 *
			 * @return true if the car is successfully added to the IRDeque; false otherwise
			 */
			bool addToIRDequeLeft();

			/**
			 * Removes the leftmost car in the IRDeque and makes it the current car.
			 * Does nothing if there is already a current car or if the IRDeque already empty.
			 *
			 * @return true if the car is successfully removed from the IRDeque; false otherwise
			 */
			bool removeFromIRDequeLeft();
	
			/**
			 * Removes the rightmost car in the IRDeque and makes it the current car.
			 * Does nothing if there is already a current car or if the IRDeque already empty.
			 *
			 * @return true if the car is successfully removed from the IRDeque; false otherwise
			 */
			bool removeFromIRDequeRight();
	
			/**
			 * Returns the ID of the leftmost car in the IRDeque.
			 *
			 * @return the ID of the leftmost car in the IRDeque; -1 if the IRDeque is empty
			 */
			int showTopOfIRDequeLeft();
	
			/**
			 * Returns the ID of the rightmost car in the IRDeque.
			 *
			 * @return the ID of the rightmost car in the IRDeque; -1 if the IRDeque is empty
			 */
			int showTopOfIRDequeRight();
	
			/**
			 * Returns the number of cars in the IRDeque.
			 *
			 * @return the number of cars in the IRDeque
			 */
			int showSizeOfIRDeque();
	
			//Output-Restricted Deque---------------------------------------------
			/**
			 * Adds the current car to the ORDeque on the left side.  After this operation, there should be no current car.
			 * Does nothing if there is no current car or if the ORDeque is already full.
			 *
			 * @return true if the car is successfully added to the ORDeque; false otherwise
			 */
			bool addToORDequeLeft();
	
			/**
			 * Adds the current car to the ORDeque on the right side.  After this operation, there should be no current car.
			 * Does nothing if there is no current car or if the ORDeque is already full.
			 *
			 * @return true if the car is successfully added to the ORDeque; false otherwise
			 */
			bool addToORDequeRight();
	
			/**
			 * Removes the leftmost car in the ORDeque and makes it the current car.
			 * Does nothing if there is already a current car or if the ORDeque already empty.
			 *
			 * @return true if the car is successfully removed from the ORDeque; false otherwise
			 */
			bool removeFromORDequeLeft();
	
			/**
			 * Returns the ID of the leftmost car in the ORDeque.
			 *
			 * @return the ID of the leftmost car in the ORDeque; -1 if the ORDeque is empty
			 */
			int showTopOfORDequeLeft();
	
			/**
			 * Returns the number of cars in the ORDeque.
			 *
			 * @return the number of cars in the ORDeque
			 */
			int showSizeOfORDeque();
};

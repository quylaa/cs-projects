// Written by Aleks Christensen

#include "Station.h"

Station::Station(){
    //stak->push(3);
    //que->pushTop(8);
    //deq->pushTop(2);
    //deq->pushBottom(7);
}
Station::~Station(){}

bool Station::checkId(int car) // check if given car id exists in any structure
{
	if (stak->empty() && que->empty() && deq->empty()) return true; // if all structures are empty, then id doesn't exist
	else
	{
        if (stak->find(car)) return false;
        if (que->find(car)) return false;
        if (deq->find(car)) return false;
	}
	return true;
}

bool Station::addToStation(int car)
{
	if (currentCar) return false; // must deal with current car before adding a new one
	if (car <= 0) return false; // cannot have negative IDs
	if (!Station::checkId(car)) return false; // car already exists

	currentCar = car;
	return true;
}

int Station::showCurrentCar()
{
	if (!currentCar) return -1;
	return currentCar;
}

bool Station::removeFromStation()
{
	if (currentCar)
	{
		currentCar = 0;
		if (currentCar == 0) return true;
		else return false;
	}
	return false;
}

bool Station::addToStack()
{
	if (!currentCar) return false;
	else if (stak->size() == SIZE) return false;
	else
	{
		stak->push(currentCar);
		currentCar = 0;
		return true;
	}
}

bool Station::removeFromStack()
{
	if (currentCar) return false;
	else if (stak->empty()) return false;
	else
	{
		currentCar = stak->showTop();
		stak->pop();
		return true;
	}
}

int Station::showTopOfStack()
{
	if (stak->empty()) return -1;
	else return stak->showTop();
}

int Station::showSizeOfStack()
{
	return stak->size();
}

bool Station::addToQueue()
{
    if (!currentCar) return false;
    else if (que->size() >= SIZE) return false;
    else
    {
        que->pushBottom(currentCar);
        currentCar = 0;
        return true;
    }
}

bool Station::removeFromQueue()
{
    if (currentCar) return false;
    else if (que->empty()) return false;
    else
    {
        currentCar = que->showTop();
        que->popTop();
        return true;
    }
}

int Station::showTopOfQueue()
{
    if (que->empty()) return -1;
    else return que->showTop();
}

int Station::showSizeOfQueue()
{
    return que->size();
}

bool Station::addToDequeLeft()
{
    if (!currentCar) return false;
    else if (deq->size() >= SIZE) return false;
    else
    {
        deq->pushTop(currentCar);
        currentCar = 0;
        return true;
    }
}

bool Station::addToDequeRight()
{
    if (!currentCar) return false;
    else if (deq->size() >= SIZE) return false;
    else
    {
        deq->pushBottom(currentCar);
        currentCar = 0;
        return true;
    }
}

bool Station::removeFromDequeLeft()
{
    if (currentCar) return false;
    else if (deq->empty()) return false;
    else
    {
        currentCar = deq->showTop();
        deq->popTop();
        return true;
    }
}

bool Station::removeFromDequeRight()
{
    if (currentCar) return false;
    else if (deq->empty()) return false;
    else
    {
        currentCar = deq-> showBottom();
        deq->popBottom();
        return true;
    }
}

int Station::showTopOfDequeLeft()
{
    if (deq->empty()) return -1;
    else return deq->showTop();
}

int Station::showTopOfDequeRight()
{
    if (deq->empty()) return -1;
    else return deq->showBottom();
}

int Station::showSizeOfDeque()
{
    return deq->size();
}

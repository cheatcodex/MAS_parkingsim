/*
File: station_agent.cpp
Functions:
	1. Constructor
	2. Broadcast availability
	3. Update availability
*/

#include "station_agent.h"
#include "doublylinkedlist.h"
#include <string>
#include <iostream>
#include <cmath>
#include <vector>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>		/*time*/

using namespace std;

template<> StationAgent<spot*, int>::StationAgent()
{}

template<> StationAgent<spot*, int>::~StationAgent()
{
	spots->Clear();
	cout << "StationAgent Class Destructor" <<endl;
}

template<> void StationAgent<spot*, int>::initStationAgent(DoubleLinkList<spot*, int>* theSpotList)
{
	//srand(time(NULL));
	length = rand() % 5 + 20;
	spots = theSpotList;
}

template<> int StationAgent<spot*, int>::getTotSpots()
{
	return length;
}

template<> DoubleLinkList<spot*, int>* StationAgent<spot*, int>::getStationSpotList()
{
	return spots;
}

spot::spot()
{}
spot::spot(int x, int y, int avail)
	:location_x(x), location_y(y), availability(avail)
{}
spot::~spot()
{}

void spot::initSpot()	//call this function right after the constructor
{
	//srand(time(NULL));
	location_x = rand() % 5 + 10;
	//srand(time(NULL));
	location_y = rand() % 5 +10;
	return;	
}
bool spot::checkSpot(DoubleLinkList<spot*, int>* theSpotList)
{
	if (theSpotList->Size() == 0)
		return 1;
	DoubleNode<spot*, int>* currentSpot = theSpotList->head;
	while (currentSpot != NULL)
	{
		if (location_x == currentSpot->element->location_x && location_y == currentSpot->element->location_y)
			return 0;
		else
			currentSpot = currentSpot->next;
	}
	if (currentSpot == NULL)
		return 1;
}
bool spot::updateSpot(int avail)
{
	if (avail == availability)
		return false;
	else
	{
		availability = avail;
		return true;
	}
}
void spot::updateAvailability(int avail)
{
	availability = avail;
}
int spot::getAvailabilityofSpot ()
{
	return availability;
}

int spot::getLocationXofSpot ()
{	return location_x;}
int spot::getLocationYofSpot ()
{	return location_y;}


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
template<typename T, typename T2>
StationAgent<T, T2>::StationAgent()
{}
template<typename T, typename T2>
StationAgent<T, T2>::~StationAgent()
{
	spots.Clear();
	cout << "StationAgent Class Destructor" <<endl;
}

template<typename T, typename T2>
void StationAgent<T, T2>::initStationAgent()
{
	srand(time(NULL));
	length = rand() % 5 + 20;
	DoubleLinkList* spotList = new DoubleLinkList();
	spots = spotList;
}
template<typename T, typename T2>
int StationAgent<T, T2>::getTotSpots()
{
	return length;
}
template<typename T, typename T2>
DoubleLinkList<T, T2>* StationAgent<T, T2>::getStationSpotList()
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
	srand(time(NULL));
	location_x = rand() % 5 + 5;
	srand(time(NULL));
	location_y = rand() % 5 +10;
	return;	
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

int spot::getAvailabilityofSpot ()
{
	return availability;
}



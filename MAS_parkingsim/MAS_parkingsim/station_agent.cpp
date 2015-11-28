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

StationAgent<spot*, int>::StationAgent()
{}

StationAgent<spot*, int>::~StationAgent()
{
	spots->Clear();
	cout << "StationAgent Class Destructor" <<endl;
}

void StationAgent<spot*, int>::initStationAgent()
{
	srand(time(NULL));
	length = rand() % 5 + 20;
	DoubleLinkList<spot*, int>* spotList = new DoubleLinkList<spot*, int>();
	spots = spotList;
}

int StationAgent<spot*, int>::getTotSpots()
{
	return length;
}

DoubleLinkList<spot*, int>* StationAgent<spot*, int>::getStationSpotList()
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



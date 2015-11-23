/*
File: station_agent.cpp
Functions:
	1. Constructor
	2. Broadcast availability
	3. Update availability
*/

#include "car_agent.h"
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

StationAgent::StationAgent(int setLength, class doublylinkedlist* stationSpotList)
	:length(setLength), spots(stationSpotList)
{}

StationAgent::~StationAgent()
{
	spots.Clear();
	cout << "StationAgent Class Destructor" <<endl;
}

int StationAgent::getTotSpots()
{
	return length;
}
doublylinkedlist* StationAgent::getStationSpotList()
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



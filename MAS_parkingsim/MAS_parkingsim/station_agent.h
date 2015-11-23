/*
File Name: station_agent.h
*/

#ifndef STATION_AGENT_H
#define STATION_AGENT_H

//#include "car_agent.h"
//#include "station_agent.h"
//#include "MAS_lib.h"
#include <stdio.h>
#include <string>
#include <iostream>
#include <cmath>
#include <vector>
#include "doublylinkedlist.h"

using namespace std;

//template <int Tot_spots>
class StationAgent
{
	public:
		StationAgent(int setLength, class doublelinkedlist* stationSpotList);
		~StationAgent();
		class doublelinkedlist* getStationSpotList();
		//void getStationInfo();
		//void getSpotInfo(int Spot_number);
		int getTotSpots();
		//void updateStation(StationAgent& station);
	private:
		int length; // Total Spots size
		//int Avail_spots;	
		class doublelinkedlist* spots;	//spotlist: element1:spot_t, element2:0
		//vector< vector<int> > all_spots_status;
		//vector<int> this_spot_status; // 3: availability, x, y
	/* data */
};


class spot
{
private:
	int location_x;
	int location_y;	
	int availability;	//0:empty, 1:full
public:
	spot(int x, int y, int avail);
	spot();
	~spot();
	void initSpot();
	bool updateSpot(int avail);
	int getAvailabilityofSpot ();
}spot;

#endif
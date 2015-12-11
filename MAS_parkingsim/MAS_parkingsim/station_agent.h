/*
File Name: station_agent.h
*/

#ifndef STATION_AGENT_H
#define STATION_AGENT_H

#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <iostream>
#include <cmath>
#include <vector>
#include "doublylinkedlist.h"

using namespace std;
class spot
{
private:
	int location_x;
	int location_y;
	int availability;	//0:empty, 1:full
public:
	spot();
	spot(int x, int y, int avail);
	~spot();
	void initSpot();
	bool checkSpot(DoubleLinkList<spot*, int>* theSpotList);	//check if two spot are the same
	bool updateSpot(int avail);
	int getAvailabilityofSpot();
	void updateAvailability(int avail);
	int getLocationXofSpot ();
	int getLocationYofSpot ();
};
template<typename T, typename T2>
class StationAgent
{
	public:
		StationAgent();
		~StationAgent();
		//void getStationInfo();
		//void getSpotInfo(int Spot_number);
		void initStationAgent(DoubleLinkList<spot*, int>* theSpotList);
		int getTotSpots();
		DoubleLinkList<spot*, int>* getStationSpotList();
		//void updateStation(StationAgent& station);
	private:
		int length; // Total Spots size
		//int Avail_spots;	
		DoubleLinkList<spot*, int>* spots;	//spotlist: element1:spot_t, element2:0
		//vector< vector<int> > all_spots_status;
		//vector<int> this_spot_status; // 3: availability, x, y
	/* data */
};

//template<typename T, typename T2>


#endif


/*
File Name: car_agent.h
*/
#ifndef CAR_AGENT_H
#define CAR_AGENT_H

#include "station_agent.h"
#include "doublylinkedlist.h"
#include <stdio.h>
#include <string>
#include <iostream>


using namespace std;
class destination
{
public:
	spot* dest_spot;
	int Time;
public:
	destination();
	~destination();
	void updateDest(spot* new_spot, const int& time);
};
class location
{
public:
	location();
	void updateLoc(const int& x, const int& y);
	int getLocationXofCar();
	int getLocationYofCar();
private:
	int Location_x;
	int Location_y;
};
template<typename T, typename T2>
class carAgent
{
	public:
		location* my_location;
		destination* my_destination;
		DoubleLinkList<spot*, int>* spot_list;	//ptr to doublylinklist of mycar's ranked spot list

	public:
		carAgent();	//constructor
		~carAgent();	//destructor
		void initCar();	//call right after constructor
		DoubleLinkList<spot*, int>* getSpotList ();
		void updateDestination(DoubleNode<spot*, int>* spot_node);	//update my car's destination: spot*, int time
		void updateLocation(int&x, int&y);
		//updateMember not yet implemented
};


int calculateTime(spot* thespot, carAgent<spot*, int>* Mycar);	//caculate time from mycar to each of the spots (random?)
DoubleLinkList<spot*, int>* computeRank(DoubleNode<carAgent<spot*, int>*, int>*, DoubleLinkList<spot*, int>* station_spot);	//compute time to all spots and rank; save the result to a linklist.
int compareTime(carAgent<spot*, int>* Mycar, DoubleLinkList<carAgent<spot*, int>*, int>* CarList);	//compare the first option with other cars first option. If my car is the most competitive one, return 0; otherwise, point to the next option and return 1. 
int GetSortNum (DoubleLinkList<spot*, int>* rankinglist, int timeToSpot);
bool setSecondNearestDest (carAgent<spot*, int>* Mycar);	//if can' get the first spot, make dest to second spot

#endif


/*
File Name: car_agent.h
*/
#ifndef CAR_AGENT
#define CAR_AGENT

#include "car_agent.h"
#include "station_agent.h"
#include "doublylinkedlist.h"
#include <stdio.h>
#include <string>
#include <iostream>


using namespace std;

class carAgent
{
	private:
		struct location
		{
		public:
			int Location_x;
			int Location_y;
		}location;
		struct destination
		{
		public:
			spot* dest_spot;
			int Time;
		}destination;
		DoubleLinkList* spot_list;	//ptr to doublylinklist of mycar's ranked spot list

	public:
		carAgent(class Doublylinkedlist* myspotlist);	//constructor
		~carAgent();	//destructor
		void initCar();	//call right after constructor
		Doublylinkedlist* getSpotList ();
		void updateDest (class DoubleNode* spot_node);	//update my car's location and destination.
		//updateMember not yet implemented
}carAgent;



int calculateTime (const spot* spot, const carAgent* Mycar);	//caculate time from mycar to each of the spots (random?)
Doublylinkedlist* computeRank(const carAgent* car, const Doublylinkedlist* station_spot);	//compute time to all spots and rank; save the result to a linklist.
int compareTime(const carAgent* Mycar, const Doublylinkedlist* CarList);	//compare the first option with other cars first option. If my car is the most competitive one, return 0; otherwise, point to the next option and return 1. 
int GetSortNum (Doublylinkedlist* rankinglist, int timeToSpot);
bool setSecondNearestDest (const carAgent* Mycar);	//if can' get the first spot, make dest to second spot
#endif
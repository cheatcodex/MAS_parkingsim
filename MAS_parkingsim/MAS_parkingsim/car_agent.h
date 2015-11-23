/*
File Name: car_agent.h
*/
#ifndef CAR_AGENT
#define CAR_AGENT

#include "station_agent.h"
#include "doublylinkedlist.h"
#include <stdio.h>
#include <string>
#include <iostream>


using namespace std;

class carAgent
{
	public:
		struct location
		{
		public:
			int Location_x;
			int Location_y;
			location();
			bool updateLocation(int& x, int& y);
		};
		location* my_location;
		struct destination
		{
		public:
			class spot* dest_spot;
			int Time;
			destination();
			~destination();
			bool updateDest(class spot* new_spot, int& time);
		};
		destination* my_destination;
		class DoubleLinkList* spot_list;	//ptr to doublylinklist of mycar's ranked spot list

	public:
		carAgent();	//constructor
		~carAgent();	//destructor
		void initCar();	//call right after constructor
		DoubleLinkList* getSpotList ();
		void updateDestination (class DoubleNode* spot_node);	//update my car's location and destination.
		//updateMember not yet implemented
}carAgent;


template<typename T, typename T2>
int calculateTime (spot* spot, carAgent* Mycar);	//caculate time from mycar to each of the spots (random?)
template<typename T, typename T2>
DoubleLinkList* computeRank(carAgent* car, DoubleLinkList* station_spot);	//compute time to all spots and rank; save the result to a linklist.
template<typename T, typename T2>
int compareTime(carAgent* Mycar, DoubleLinkList* CarList);	//compare the first option with other cars first option. If my car is the most competitive one, return 0; otherwise, point to the next option and return 1. 
template<typename T, typename T2>
int GetSortNum (DoubleLinkList* rankinglist, int timeToSpot);
template<typename T, typename T2>
bool setSecondNearestDest (carAgent* Mycar);	//if can' get the first spot, make dest to second spot
#endif
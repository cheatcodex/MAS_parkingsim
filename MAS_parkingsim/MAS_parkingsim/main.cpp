/*
File name: main.c
Author: L. Xia, Q. Yan
Functions:
	1. Create and initialize car agents
	2. Create and initialize Station Agent(s)
	3. Link all agents in a link list (car_list)
	4. Simulation (loop till all cars are parked)
		a. Broadcast (Car: Destination and Time; Station: availabilities)
		b. Compute Destinations
		c. Update Destination and Time; Update Station availabilities
		d. Output Result(s)
	5. Output Final Result
*/

#include "car_agent.h"
#include "station_agent.h"
#include "doublylinkedlist.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;
//template<typename spot*, typename int>
#define STATION_SIZE 10
#define INITIAL_CAR_SIZE 8
int main ()
{
	//create a station
	DoubleLinkList<spot*, int>* station_spot_list = new DoubleLinkList<spot*, int>();	//create a spotlist for a station
	StationAgent<spot*, int>* thisStation = new StationAgent<spot*, int>();	//a station of 10 spots
	thisStation->initStationAgent();
	//initialize spots and put them into spot-list
	for (int i = 0; i < STATION_SIZE; i++)
	{

		spot* new_spot = new spot();
		new_spot->initSpot();
		station_spot_list->AddBack(new_spot, 0);
	}
	//create cars
	//and put them into a car-list
	DoubleLinkList<carAgent<spot*,int>*, int>* car_list = new DoubleLinkList<carAgent<spot*, int>*, int>();	//to record all the cars in the region
	for (int i = 0; i < INITIAL_CAR_SIZE; i++)
	{
		DoubleLinkList<spot*, int>* new_car_ranking_list = new DoubleLinkList<spot*, int>();	//to store the spots and time from this car
		carAgent<spot*, int>* new_car = new carAgent<spot*, int>();
		new_car->initCar();
		car_list->AddBack(new_car,0);
	}
	//simulation begins
	//rank the spots for each car
	//set the nearest spot as the destination
	DoubleNode<carAgent<spot*, int>*, int>* current_car_node = car_list->head;
	int timeToSpot;
	while (current_car_node != car_list->tail)
	{
		current_car_node->element->spot_list = computeRank(current_car_node, station_spot_list);
		current_car_node->element->updateDestination(current_car_node->element->spot_list->head);		//update destination and time
		current_car_node = current_car_node->next;
	}
	//compare cars' time to the same destination
	bool flag = 1;
	while (flag == 0)
	{
		flag = 0;
		current_car_node = car_list->head;
		while(current_car_node != car_list->tail)
		{
			if (compareTime (current_car_node->element, car_list))		//if mycar is not the most competitive one
			{
				flag = 1;	//if there is any car that has to reassign spot, loop again
				if (!setSecondNearestDest(current_car_node->element))	//set the dest to the second nearest spot
					cout<<"can't find spot for this car"<<endl;
			}
			current_car_node = current_car_node->next;
		} 
	}
	if (flag == 0)
		cout<<"end of simulation"<<endl;
}
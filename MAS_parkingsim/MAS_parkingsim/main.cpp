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

#define STATION_SIZE 10
#define INITIAL_CAR_SIZE 8
int main ()
{
	//create a station
	doublelinkedlist* station_spot_list = new doublelinkedlist ();	//create a spotlist for a station
	StationAgent* thisStation = new StationAgent(STATION_SIZE, station_spot_list)；	//a station of 10 spots
	//initialize spots and put them into spot-list
	for (int i=0, i<STATION_SIZE, i++)
	{

		spot* new_spot = new spot();
		new_spot->initSpot();
		staiton_spot_list.AddBack(new_spot, 0);
	}
	//create cars
	//and put them into a car-list
	doublylinkedlist_t car_list = new doublylinkedlist ();	//to record all the cars in the region
	for (int i = 0; i < INITIAL_CAR_SIZE; i++)
	{
		doublelinkedlist* new_car_ranking_list = new doublelinkedlist ();	//to store the spots and time from this car
		carAgent* new_car = new carAgent (new_car_ranking_list);
		new_car.initCar();
		car_list.AddBack(new_car,0);
	}
	//simulation begins
	//rank the spots for each car
	//set the nearest spot as the destination
	DoubleNode* current_car_node = car_list->head;
	int timeToSpot;
	while (current_car_node != car_list->tail)
	{
		current_car_node->element1->new_car_ranking_list = computeRank(current_car_node, station_spot_list);
		current_car_node->element1->updateDest(new_car_ranking_list->head);		//update destination and time
		current_car_node = current_car_node->next;
	}
	//compare cars' time to the same destination
	bool flag = 1;
	while (flag > 0)
	{
		flag = 0;
		current_car_node = car_list->head;
		while(current_car_node != car_list->tail)
		{
			if (compareTime (current_car_node->element1, car_list))		//if mycar is not the most competitive one
			{
				flag = 1;	//if there is any car that has to reassign spot, loop again
				if (!setSecondNerestDest(current_car_node->element1))	//set the dest to the second nearest spot
					cout<<"can't find spot for this car"<<endl;
			}
			current_car_node = current_car_node->next;
		} 
	}
	if (flag == 0)
		cout<<"end of simulation"<<endl;
}
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
#define STATION_SIZE 5
#define INITIAL_CAR_SIZE 3
int main ()
{
	//create a station
	DoubleLinkList<spot*, int>* station_spot_list = new DoubleLinkList<spot*, int>();	//create a spotlist for a station
	StationAgent<spot*, int>* thisStation = new StationAgent<spot*, int>();	//a station of 10 spots

	//initialize spots and put them into spot-list
	for (int i = 0; i < STATION_SIZE; i++)
	{

		spot* new_spot = new spot();
		new_spot->initSpot();
		station_spot_list->AddBack(new_spot, 0);
	}
	thisStation->initStationAgent(station_spot_list);
	DoubleNode<spot*, int>* current_spot_test = (thisStation->getStationSpotList())->head;
	int count =1;
	//while (current_spot_test!=(thisStation->getStationSpotList())->tail)
	while(current_spot_test !=NULL)
	{
		printf("spot#%d: x:%d, y:%d\n",count, current_spot_test->element->getLocationXofSpot(), current_spot_test->element->getLocationYofSpot());
		count++;
		current_spot_test = current_spot_test->next;
	}
	
	//printf("initialize spots and put them into spot-list: DONE!");
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
	DoubleNode<carAgent<spot*,int>*, int>* current_car_test = car_list->head;
	count =1;
	while (current_car_test!=NULL)
	{
		printf("car#%d: x:%d, y:%d\n",count, current_car_test->element->my_location->getLocationXofCar(), current_car_test->element->my_location->getLocationYofCar());
		count++;
		current_car_test = current_car_test->next;
	}
	
	//printf("create cars and put them into a car-list: DONE!");
	//simulation begins
	//rank the spots for each car
	//set the nearest spot as the destination
	DoubleNode<carAgent<spot*, int>*, int>* current_car_node = car_list->head;
	int timeToSpot;
	while (current_car_node != NULL)
	{
		current_car_node->element->spot_list = computeRank(current_car_node, station_spot_list);
		//printf("ranked time for this car: %d, %d, %d\n", current_car_node->element->spot_list->head->element2,current_car_node->element->spot_list->head->next->element2,current_car_node->element->spot_list->head->next->next->element2 );
		current_car_node->element->updateDestination(current_car_node->element->spot_list->head);		//update destination and time
		//printf("this car's initial destination(time): %d\n", current_car_node->element->my_destination->Time);
		current_car_node = current_car_node->next;
	} 
	current_car_test = car_list->head;
	count =1;
	int count_spot;
	DoubleNode<spot*, int>* rank_node_test;
	while (current_car_test!=NULL)
	{
		count_spot=1;
		rank_node_test = current_car_test->element->spot_list->head;
		while(rank_node_test!=NULL)
		{
			printf("car#%d: rankedspot#%d: x:%d, y:%d, time:%d\n",count, count_spot,rank_node_test->element->getLocationXofSpot(), rank_node_test->element->getLocationYofSpot(),rank_node_test->element2);
			count_spot++;
			rank_node_test = rank_node_test->next;
		}
		current_car_test = current_car_test->next;
		count++;
	}
	//printf("rank cars and set initial destinations: done!\n");
	//compare cars' time to the same destination
	bool flag = 1;
	while (flag != 0)
	{
		flag = 0;
		current_car_node = car_list->head;
		while(current_car_node != NULL)
		{
			if (compareTime (current_car_node->element, car_list))		//if mycar is not the most competitive one
			{
				flag = 1;	//if there is any car that has to reassign spot, loop again
				if (!setSecondNearestDest(current_car_node->element))	//set the dest to the second nearest spot
					cout<<"can't find spot for this car"<<endl;
			}
			printf("current car's destination and time: x:%d, y:%d, time:%d\n",current_car_node->element->my_destination->dest_spot->getLocationXofSpot(), current_car_node->element->my_destination->dest_spot->getLocationYofSpot(), current_car_node->element->my_destination->Time);
			current_car_node = current_car_node->next;
		} 
	}
	if (flag == 0)
	{
		current_car_test = car_list->head;
		count =1;
		while (current_car_test!=NULL)
		{
			printf("car#%d: final destination: x:%d, y:%d, time:%d\n",count, current_car_test->element->my_destination->dest_spot->getLocationXofSpot(), current_car_test->element->my_destination->dest_spot->getLocationYofSpot(), current_car_test->element->my_destination->Time);
			count++;
			current_car_test = current_car_test->next;
		}
		cout<<"end of simulation"<<endl;
	}
	return 0;
}




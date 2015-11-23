/*
Name: car_agent.c
Functions:
	1. Struct Constructor
	2. Struct Destructor
	3. Compute time to all spots and rank
	4. Set to nearest/fastest destination
	5. Broadcast
	6. Compare
	7. Update destination and time
*/

#include "car_agent.h"
#include "station_agent.h"
#include "doublylinkedlist.h"
#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <time.h>
//#include <vector>
using namespace std;

carAgent::location::location()
	:location_x(0), location_y(0)	//initialization to be modified
{}

carAgent::destination::destination()
	: Destination_x(0), Destination_y(0), Time(0)
{}

carAgent::carAgent(class Doublylinkedlist* myspotlist)
	:spot_list(myspotlist);
{}

carAgent::~carAgent()
{spot_list->Clear();}

void carAgent::initCar()
{
	srand(time(NULL));
	location.Location_x = rand() % 5 + 5;
	srand(time(NULL));
	location.Location_y = rand() % 5 + 5;
}

Doublylinkedlist* carAgent::getSpotList ()
{
	return spot_list;
}

void carAgent::updateDest(class DoubleNode* spot_node)
{
	destination.dest_spot = spot_node->element1;
	destination.Time = spot_node->element2;
}

int GetSortNum(Doublylinkedlist* rankinglist, int timeToSpot)
{
	DoubleNode* currentSpot = rankinglist->head;
	int time_currentSpot;
	int count = 1;
	while (currentSpot != rankinglist->tail)
	{
		time_currentSpot = currentSpot->element2;
		if (timeToSpot >= time_currentSpot)
			return count;
		else
		{
			currentSpot = currentSpot->next;
			count ++;
		}
	}
}

Doublylinkedlist* computeRank(const carAgent* car, const Doublylinkedlist* station_spot)
{
	Doublylinkedlist* ranking = new Doublylinkedlist;
	DoubleNode* currentSpot = station_spot->head;	//DoubleNode<spot_t, timefromcartospot>
	if (Doublylinkedlist.isempty())
		return NULL;
	srand(time(NULL));
	int time_car_spot = rand() % 5 + 5;
	ranking.AddFront(currentSpot->element1, time_car_spot)；	//first spot in the list  
	currentSpot = currentSpot->next;
	while (currentSpot != station_spot->tail)
	{
		srand(time(NULL));
		time_car_spot = rand() % 5 + 5;
		int sortNum = GetSortNum(ranking, time_car_spot);
		ranking.AddNodeAt (currentSpot->element1, time_car_spot , sortNum);
	}
	return ranking;
}

int compareTime(const carAgent* Mycar, const Doublylinkedlist* CarList)	//arg Firstcar: head of the linked list of cars
{
	DoubleNode* currentCar = CarList->head;	//DoubleNode<car, timetodestination>
	while (currentCar != CarList->tail)
	{
		if (Mycar->destination_t->dest_spot == currentCar->destination_t->dest_spot)
		{
			if (Mycar->destination_t->Time < currentCar->element2)
				return 1;
		}
		else 
			currentCar = currentCar->next;
	}
		if (current == CarList->tail)
			return 0;
}

bool setSecondNearestDest (const carAgent* Mycar)
{
	Mycar.updateDest(Mycar->spot_list->head->next);
	if (!Mycar->spotlist.(RemoveFront))
	{
		return false;
	}
	return true;
}






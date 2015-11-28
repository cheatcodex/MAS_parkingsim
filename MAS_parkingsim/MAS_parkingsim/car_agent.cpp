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

location::location()
	:Location_x(0), Location_y(0)	//initialization to be modified
{}

destination::destination()
	: dest_spot(NULL), Time(0)
{}
destination::~destination()
{
	delete dest_spot;
}

void location::updateLoc(int& x, int& y)
{
	Location_x = x;
	Location_y = y;
}

void destination::updateDest(class spot* new_spot, int& time)
{
	dest_spot = new_spot;
	Time = time;
}

carAgent<spot*, int>::carAgent()
{}

carAgent<spot*, int>::~carAgent()
{
	spot_list->Clear();
}

void carAgent<spot*, int>::updateLocation(int&x, int&y)
{
	my_location->updateLoc(x, y);
}
void carAgent<spot*, int>::initCar()	//init update location of my car
{
	srand(time(NULL));
	int x= rand() % 5 + 5;
	srand(time(NULL));
	int y= rand() % 5 + 5;
	location* location_m = new location();
	updateLocation(x, y);
	my_location = location_m;
	DoubleLinkList<spot*, int>* spotList = new DoubleLinkList<spot*, int>();
	spot_list = spotList;
}

DoubleLinkList<spot*, int>* carAgent<spot*, int>::getSpotList ()
{
	return spot_list;
}

void carAgent<spot*, int>::updateDestination (DoubleNode<spot*, int>* spot_node)
{
	destination* destination_m = new destination();
	class spot* nearest_spot = spot_node->element;
	int time = spot_node->element2;
	destination_m->updateDest(nearest_spot, time);
	my_destination = destination_m;
}


int GetSortNum(DoubleLinkList<spot*, int>* rankinglist, int timeToSpot)
{
	DoubleNode<spot*, int>* currentSpot = rankinglist->head;
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

DoubleLinkList<spot*, int>* computeRank(DoubleNode<carAgent<spot*, int>*, int>*, DoubleLinkList<spot*, int>* station_spot)
{
	DoubleLinkList<spot*, int>* ranking = new DoubleLinkList<spot*, int>();
	DoubleNode< spot*, int>* currentSpot = station_spot->head;	//DoubleNode<spot_t, timefromcartospot>
	if (ranking->isempty())
		return NULL;
	srand(time(NULL));
	int time_car_spot = rand() % 5 + 5;
	ranking->AddFront(currentSpot->element, time_car_spot);	//first spot in the list  
	currentSpot = currentSpot->next;
	while (currentSpot != station_spot->tail)
	{
		srand(time(NULL));
		time_car_spot = rand() % 5 + 5;
		int sortNum = GetSortNum(ranking, time_car_spot);
		ranking->AddNodeAt (currentSpot->element, time_car_spot , sortNum);
	}
	return ranking;
}

int compareTime(carAgent<spot*, int>* Mycar, DoubleLinkList<carAgent<spot*, int>*, int>* CarList)	//arg Firstcar: head of the linked list of cars
{
	DoubleNode<carAgent<spot*, int>*, int>* currentCar = CarList->head;	//DoubleNode<car, timetodestination>
	while (currentCar != CarList->tail)
	{
		if (Mycar->my_destination->dest_spot == currentCar->element->my_destination->dest_spot)
		{
			if (Mycar->my_destination->Time < currentCar->element2)
				return 1;
		}
		else 
			currentCar = currentCar->next;
	}
		if (currentCar == CarList->tail)
			return 0;
}

bool setSecondNearestDest (carAgent<spot*, int>* Mycar)
{
	Mycar->updateDestination(Mycar->spot_list->head->next);
	if (!(Mycar->spot_list->RemoveFront()))
	{
		return false;
	}
	return true;
}






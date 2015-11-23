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

carAgent::carAgent()
{
		
}
template<typename T, typename T2>
carAgent::~carAgent()
{
	spot_list->Clear();
}

carAgent::location::location()
	:Location_x(0), Location_y(0)	//initialization to be modified
{}

carAgent::destination::destination()
	: dest_spot(NULL), Time(0)
{}
carAgent::destination::~destination()
{
	delete dest_spot;
}

bool carAgent::location::updateLocation(int& x, int& y)
{
	Location_x = x;
	Location_y = y;
}
bool carAgent::destination::updateDest(class spot* new_spot, int& time)
{
	dest_spot = new_spot;
	Time = time;
}
template<typename T, typename T2>
void carAgent::initCar()	//init update location of my car
{
	srand(time(NULL));
	int x= rand() % 5 + 5;
	srand(time(NULL));
	int y= rand() % 5 + 5;
	location* location_m = new location();
	location_m->updateLocation(x, y);
	my_location = location_m;
	DoubleLinkList* spotList = new DoubleLinkList();
	spot_list = spotList;
}

DoubleLinkList* carAgent::getSpotList ()
{
	return spot_list;
}
template<typename T, typename T2>
void carAgent::updateDestination (class DoubleNode* spot_node)
{
	destination* destination_m = new destination();
	class spot* nearest_spot = spot_node->element1;
	int time = spot_node->element2;
	destination_m->updateDest(nearest_spot, time);
	my_destination = destination_m;
}
template<typename T, typename T2>
int GetSortNum(DoubleLinkList* rankinglist, int timeToSpot)
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
template<typename T, typename T2>
DoubleLinkList* computeRank(carAgent* car, DoubleLinkList* station_spot)
{
	DoubleLinkList* ranking = new DoubleLinkList();
	DoubleNode* currentSpot = station_spot->head;	//DoubleNode<spot_t, timefromcartospot>
	if (*ranking.isempty())
		return NULL;
	srand(time(NULL));
	int time_car_spot = rand() % 5 + 5;
	ranking->AddFront(currentSpot->element1, time_car_spot);	//first spot in the list  
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
template<typename T, typename T2>
int compareTime(carAgent* Mycar, DoubleLinkList* CarList)	//arg Firstcar: head of the linked list of cars
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
template<typename T, typename T2>
bool setSecondNearestDest (carAgent* Mycar)
{
	Mycar->updateDest(Mycar->spot_list->head->next);
	if (!(Mycar->spotlist.RemoveFront()))
	{
		return false;
	}
	return true;
}






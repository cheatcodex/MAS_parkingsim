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

void location::updateLoc(const int& x, const int& y)
{
	Location_x = x;
	Location_y = y;
}
int location::getLocationXofCar()
{
	return Location_x;
}
int location::getLocationYofCar()
{
	return Location_y;
}
void destination::updateDest(class spot* new_spot, const int& time)
{
	dest_spot = new_spot;
	Time = time;
}

template<> carAgent<spot*, int>::carAgent()
{}

template<> carAgent<spot*, int>::~carAgent()
{
	spot_list->Clear();
}

template<> void carAgent<spot*, int>::updateLocation(int&x, int&y)
{
	my_location->updateLoc(x, y);
}
template<> void carAgent<spot*, int>::initCar()	//init update location of my car
{
	//srand(time(NULL));
	int r1 = rand();
	int x = rand() % 10 + 1;
	//printf("rand 1 %d \t",r1);
	//printf("x location: %d ",x);
	r1 = rand();
	int y = rand() % 10 + 1;
	//printf("y location: %d \n", y);
	//printf("rand 2 %d \n", r1);
	location* location_m = new location();
	destination* destination_m = new destination();
	my_destination = destination_m;
	my_location = location_m;
	updateLocation(x, y);
	DoubleLinkList<spot*, int>* spotList = new DoubleLinkList<spot*, int>();
	spot_list = spotList;
}

template<> DoubleLinkList<spot*, int>* carAgent<spot*, int>::getSpotList()
{
	return spot_list;
}

template<> void carAgent<spot*, int>::updateDestination(DoubleNode<spot*, int>* spot_node)
{
	class spot* nearest_spot = spot_node->element;
	int time = spot_node->element2;
	my_destination->updateDest(nearest_spot, time);
}


int GetSortNum(DoubleLinkList<spot*, int>* rankinglist, int timeToSpot)
{
	DoubleNode<spot*, int>* currentSpot = rankinglist->head;
	int time_currentSpot;
	int count = 1;
	
	if (rankinglist->Size() <= 1)
	{
		time_currentSpot = currentSpot->element2;
		if (timeToSpot > time_currentSpot)
			return count + 1;
		else
			return count;
	}
	else // size >=2
	{
		while (currentSpot != rankinglist->tail)
		{
			time_currentSpot = currentSpot->element2;
			if (timeToSpot <= time_currentSpot)
			{
				return count;
			}
			else// //timeToSpot > time_currentSpot
			{
				count++;
				currentSpot = currentSpot->next;
			}
		}
		if (currentSpot == rankinglist->tail)
		{
			time_currentSpot = currentSpot->element2;
			if (timeToSpot > time_currentSpot)
			{
				return count+1;
			}
			else
				return count;
		}
	}
}

DoubleLinkList<spot*, int>* computeRank(DoubleNode<carAgent<spot*, int>*, int>*, DoubleLinkList<spot*, int>* station_spot)
{
	DoubleLinkList<spot*, int>* ranking = new DoubleLinkList<spot*, int>();
	DoubleNode< spot*, int>* currentSpot = station_spot->head;	//DoubleNode<spot_t, timefromcartospot>
																//srand(time(NULL));
	int time_car_spot = rand() % 5 + 5;
	ranking->AddFront(currentSpot->element, time_car_spot);	//first spot in the list  
	currentSpot = currentSpot->next;
	while (currentSpot != station_spot->tail)
	{
		//srand(time(NULL));
		time_car_spot = rand() % 5 + 5;
		int sortNum = GetSortNum(ranking, time_car_spot);
		ranking->AddNodeAt(currentSpot->element, time_car_spot, sortNum);
		currentSpot = currentSpot->next;
	}
	return ranking;
}

int compareTime(carAgent<spot*, int>* Mycar, DoubleLinkList<carAgent<spot*, int>*, int>* CarList)	//arg Firstcar: head of the linked list of cars
{
	int compete = 0;
	DoubleNode<carAgent<spot*, int>*, int>* currentCar = CarList->head;	//DoubleNode<car, timetodestination>
	while (currentCar != CarList->tail)
	{
		if (currentCar->element == Mycar)
		{
			currentCar = currentCar->next;
		}
		else
		{
			if (Mycar->my_destination->dest_spot->getAvailabilityofSpot())//full
				return 1;
			if (Mycar->my_destination->dest_spot == currentCar->element->my_destination->dest_spot)
			{
				if (Mycar->my_destination->Time > (currentCar->element->my_destination->Time))
					return 1;
				else if (Mycar->my_destination->Time = (currentCar->element->my_destination->Time))
					compete = 1;
				currentCar = currentCar->next;
			}
			else
				currentCar = currentCar->next;
		}
	}
	if (currentCar == CarList->tail)
	{
		if (Mycar->my_destination->dest_spot->getAvailabilityofSpot())//full
			return 1;
		if (Mycar->my_destination->dest_spot== currentCar->element->my_destination->dest_spot)
		{
			if (Mycar->my_destination->Time > (currentCar->element->my_destination->Time))
				return 1;
		}
		//if (compete == 1)
		Mycar->my_destination->dest_spot->updateAvailability(1);
		return 0;
	}
}

bool setSecondNearestDest(carAgent<spot*, int>* Mycar)
{
	if (Mycar->spot_list->head->next == NULL)
		return false;
	Mycar->updateDestination(Mycar->spot_list->head->next);
	if (!(Mycar->spot_list->RemoveFront()))
	{
		return false;
	}
	return true;
}


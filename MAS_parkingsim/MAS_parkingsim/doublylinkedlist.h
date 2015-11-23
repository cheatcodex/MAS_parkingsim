//doublylinkedlist.h

#ifndef LINKEDLIST
#define LINKEDLIST

#include <stdlib.h>
#include <stdio.h>
#include <iostream>

using namespace std;

template<typename T, typename T2>

class DoubleNode
{
public:
	T element;
	T2 element2;
	DoubleNode* prev;
	DoubleNode* next;
	DoubleNode(const T& theElement, const T2& theElement2, DoubleNode* Prev, DoubleNode* Next);
};

class DoubleLinkList
{
private:
	class DoubleNode* head;
	class DoubleNode* tail;
	int size;
public:
	DoubleLinkList();
	~DoubleLinkList();
	int Size();
	bool isempty();
	class DoubleNode* GetPointAt(int pos);
	bool AddNodeAt (T val, T2 val2, int pos);
	void AddBack(T val, T2 val2);
	void AddFront(T val, T2 val2);
	void Clear();
	bool RemoveBack();
	bool RemoveFront();
	bool RemoveAt(int pos);
};

#endif
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
	DoubleNode<T, T2>* prev;
	DoubleNode<T, T2>* next;
	DoubleNode(const T& theElement, const T2& theElement2, DoubleNode* Prev, DoubleNode* Next);
};

template<typename T, typename T2>
class DoubleLinkList 
{
public:
	class DoubleNode<T, T2>* head;
	class DoubleNode<T, T2>* tail;
	int size;
public:
	DoubleLinkList();
	~DoubleLinkList();
	int Size();
	bool isempty();
	class DoubleNode<T,T2>* GetPointAt(int pos);

	bool AddNodeAt (T val, T2 val2, int pos);

	void AddBack(T val, T2 val2);

	void AddFront(T val, T2 val2);
	void Clear();
	bool RemoveBack();
	bool RemoveFront();
	bool RemoveAt(int pos);
};

#endif
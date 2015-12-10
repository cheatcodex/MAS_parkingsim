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
	//functions
	DoubleNode(){}
	DoubleNode(const T& theElement, const T2& theElement2)
	:element(theElement), element2(theElement2){}
};

template<typename T, typename T2>
class DoubleLinkList 
{
public:
	DoubleNode<T, T2>* head;
	DoubleNode<T, T2>* tail;
	int size;
public:
	DoubleLinkList(){}
	~DoubleLinkList()
	{Clear();}
	
	int Size()
	{return size;}
	
	bool isempty()
	{return size==0?true:false;}
	
	DoubleNode<T,T2>* GetPointAt(int pos)
	{  
		DoubleNode<T, T2>* pNode=NULL;  
		if (pos<=0 || pos>size)  
			std::cout<<"out of range"<<std::endl;  
		else  
		{  
			pNode=head;  
			for (int i=1;i<=pos-1;++i)  
				pNode=pNode->next;  
		}  
		return pNode;  
	}  
	
	bool AddNodeAt (const T& val, const T2& val2, int pos)
	{
		DoubleNode<T, T2>* pNode=NULL;  
		if (pos<=0 || pos>size)  
		{  
			std::cout<<"out of range"<<std::endl;  
			return false;  
		}  
		if (pos==size)  
			AddBack(val, val2);  
		else if (pos==1)  
			AddFront(val, val2);  
		else  
		{  
			DoubleNode<T, T2>* pPreNode=GetPointAt(pos-1);  
			pNode=new DoubleNode<T, T2>(val,val2);  
			pNode->next=pPreNode->next;  
			pNode->prev=pPreNode;  
			pPreNode->next->prev=pNode;    
			pPreNode->next=pNode;  
		}  
		size++;  
		return true;  
	}
	void AddBack(const T& val, const T2& val2)
	{  
		DoubleNode<T, T2>* pNode=new DoubleNode<T, T2>(val, val2);  
		if (isempty())  
		{  
			head=pNode;  
			tail=pNode;  
		}  
		else  
		{  
			tail->next=pNode;  
			pNode->prev=tail;  
			tail=pNode;  
		}  
		size++;  
	} 
	void AddFront(const T& val, const T2& val2)
	{  
		DoubleNode<T, T2>* pNode=new DoubleNode<T, T2>(val, val2);  
		if (isempty())  
		{  
			head=pNode;  
			tail=pNode;  
		}  
		else  
		{  
			head->prev=pNode;  
			pNode->next=head;  
			head=pNode;  
		}  
		size++;  
	}  
	void Clear()
	{  
		const int nums=Size();  
		if (!isempty())  
		{  
			for (int k=1;k<=nums;++k)  
			{  
				DoubleNode<T,T2>* temp=head->next;  
				delete head;  
				head=temp;  
				size--;  
			}  
		}  
	}  
	
	bool RemoveBack()
	{  
		return RemoveAt(size);  
	}  
	bool RemoveFront()
	{  
		return RemoveAt(1);  
	} 
	bool RemoveAt(int pos)
	{  
		DoubleNode<T, T2>* pNode=NULL;  
		if (isempty())  
		{  
			std::cout<<"the link list is empty"<<std::endl;  
			return false;  
		}  
		if (pos<=0 || pos>size)  
		{  
			std::cout<<"out of range"<<std::endl;  
			return false;  
		}  
		if (size==1)  
		{  
			Clear();  
		}  
		if (pos==1)  
		{  
			pNode=head;  
			head=head->next;  
			head->prev=NULL;  
			delete pNode;  
		}  
		else  
		{  
			DoubleNode<T, T2>* pPreNode=GetPointAt(pos-1);  
			pNode=pPreNode->next;  
			if (pos==size)  
			{   
				pPreNode->next=NULL;  
				tail=pPreNode;  
			}   
			else  
			{  
				pPreNode->next=pNode->next;  
				pNode->next->prev=pPreNode;  
			}  
			delete pNode;  
		}  
		size--;  
		return true;  
	} 
};

#endif

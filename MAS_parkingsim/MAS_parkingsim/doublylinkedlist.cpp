//doublylinkedlist.cpp
#include "doublylinkedlist.h"
#include <iostream>
#include <string>

using namespace std;

DoubleNode::DoubleNode(const T& theElement, const T2& theElement2, DoubleNode* Prev, DoubleNode* Next)
	:element1(theElement), element2(theElement2), prev(Prev), next(Next)
{}

DoubleLinkList::DoubleLinkList ()
	:head(NULL),tail(NULL),size(0)
{}

DoubleLinkList::~DoubleLinkList()
{clear();}

int DoubleLinkList::Size()
{return size;}

bool DoubleLinkList::isempty()
{return size==0?true:false;}

void DoubleLinkList::Clear()  
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

DoubleNode<T, T2>* DoubleLinkList::GetPointAt(int pos)  
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
bool DoubleLinkList::AddNodeAt (T val, T2 val2, int pos)
{
	DoubleNode<T, T2>* pNode=NULL;  
    if (pos<=0 || pos>size)  
    {  
        std::cout<<"out of range"<<std::endl;  
        return false;  
    }  
    if (pos==size)  
        AddBack(size);  
    else if (pos==1)  
        AddFront(1);  
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
void DoubleLinkList::AddFront(T val, T2 val2)  
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
void DoubleLinkList::AddBack(T val, T2 val2)  
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

bool DoubleLinkList::RemoveBack()  
{  
    return RemoveAt(size);  
}  
bool DoubleLinkList::RemoveFront()  
{  
    return RemoveAt(1);  
}  
bool DoubleLinkList::RemoveAt(int pos)  
{  
    DoubleNode<T>* pNode=NULL;  
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
        DoubleNode<T>* pPreNode=GetPointAt(pos-1);  
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
//doublylinkedlist.cpp
#include "doublylinkedlist.h"
#include <iostream>
#include <string>

using namespace std;
template<typename T, typename T2>
DoubleNode<T,T2>::DoubleNode(const T& theElement, const T2& theElement2, DoubleNode* Prev, DoubleNode* Next)
	:element1(theElement), element2(theElement2), prev(Prev), next(Next)
{}
template<typename T, typename T2>
DoubleLinkList<T, T2>::DoubleLinkList ()
	:head(NULL),tail(NULL),size(0)
{}
template<typename T, typename T2>
DoubleLinkList<T, T2>::~DoubleLinkList()
{Clear();}

template<typename T, typename T2>
int DoubleLinkList<T, T2>::Size()
{return size;}

template<typename T, typename T2>
bool DoubleLinkList<T, T2>::isempty()
{return size==0?true:false;}

template<typename T, typename T2>
void DoubleLinkList<T, T2>::Clear()
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

template<typename T, typename T2>
DoubleNode<T, T2>* DoubleLinkList<T, T2>::GetPointAt(int pos)
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
template<typename T, typename T2>
bool DoubleLinkList<T, T2>::AddNodeAt (T val, T2 val2, int pos)
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
template<typename T, typename T2>
void DoubleLinkList<T, T2>::AddFront(T val, T2 val2)
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
template<typename T, typename T2>
void DoubleLinkList<T, T2>::AddBack(T val, T2 val2)
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
template<typename T, typename T2>
bool DoubleLinkList<T, T2>::RemoveBack()
{  
    return RemoveAt(size);  
}  
template<typename T, typename T2>
bool DoubleLinkList<T, T2>::RemoveFront()
{  
    return RemoveAt(1);  
}  
template<typename T, typename T2>
bool DoubleLinkList<T, T2>::RemoveAt(int pos)
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
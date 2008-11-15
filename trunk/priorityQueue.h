#ifndef _PRIORITY_QUEUE_H
#define _PRIORITY_QUEUE_H

#include <cstdio>
#include <new>
#include "action.h"

using namespace Action;

/*****************************************
 * Queue template class
*****************************************/
template <class T>
class Queue
{
public:
	Queue();	
	~Queue();
	void Insert(T &Data);
	T Remove();
	
	/*****************************************/
	bool isEmpty()const
	{	return (m_Tail != m_Head) ? false : true ;	};


private:
	typedef struct element
	{
		T Data;
		element *Next;
	}Element;
	Element *m_Head,*m_Tail;

};


/*****************************************
 * Priority Queue class -- implemets
 * the templatized class Queue
 *****************************************/
class PriorityQueue
{
public:
	PriorityQueue(short int priorities);
	~PriorityQueue();
	
	void Insert(c_Action *job);
	c_Action* Remove();

	bool isEmpty()const
	{
		if(m_Queue)
		{
			for(int i=0;i<m_Priorities;i++)
			{
				if(!m_Queue[i].isEmpty())
					return false;
			}
			return true;
		}
		else 
			return true;
	};


private:
	Queue <c_Action*> *m_Queue;
	short int m_Priorities;
};


#endif


#include "priorityQueue.h"
#include "action.h"



/*****************************************
 * generic queue implementation
*****************************************/

template <class T>
Queue<T>::Queue()
{
	m_Head = new Element;
	m_Head->Next = NULL;
	m_Tail = m_Head;
};

template <class T>
Queue<T>::~Queue()
{
	Element *node;
	while(m_Tail != NULL)
	{
		node = m_Tail;
		m_Tail = m_Tail->Next;
		delete (node);
	}
};

template <class T>
void Queue<T>::Insert(T &Data)
{
	m_Head->Data = Data;
	m_Head->Next = new Element;
	m_Head = m_Head->Next;
	m_Head->Next = NULL;
};

template <class T>
T Queue<T>::Remove()
{
	Element *node;
	T info;
	node = m_Tail;
	m_Tail = m_Tail->Next;
	info = node->Data;
	delete (node);
	return info;
};



/*****************************************
 * priority queue implementation 
*****************************************/


PriorityQueue::PriorityQueue(short int priorities)
	:m_Priorities(priorities)
{
	m_Queue = new Queue<c_Action*> [m_Priorities];
};

PriorityQueue::~PriorityQueue()
{
	delete [] m_Queue;
};

void PriorityQueue::Insert(c_Action *job)
{
	m_Queue[job->GetPriority()].Insert(job);
};

c_Action* PriorityQueue::Remove()
{
	for(short int index = m_Priorities;index >= 0;index--)
	{
		if(!m_Queue[index].isEmpty())
			return m_Queue[index].Remove();
	}
	return NULL;
};






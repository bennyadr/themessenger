
#include "PriorityQueue.h"
#include "action.h"


Queue::Queue()
{
	m_Head = new Element;
	m_Head->Next = NULL;
	m_Tail = m_Head;
};

Queue::~Queue()
{
	Element *node;
	while(m_Tail != NULL)
	{
		node = m_Tail;
		m_Tail = m_Tail->Next;
		delete (node);
	}
};

void Queue::Insert(T &Data)
{
	m_Head->Data = Data;
	m_Head->Next = new Element;
	m_Head = m_Head->Next;
	m_Head->Next = NULL;
};

Data& Queue::Remove()
{
	Element *node;
	Data info;
	node = m_Tail;
	m_Tail = m_Tail->Next;
	info = node->Data;
	delete (node);
	return info;
};

void PriorityQueue::PriorityQueue(short int priorities)
	:m_Priorities(priorities)
{
	m_Queue = new Queue<c_Action>[priorities];
};

void PriorityQueue::~PriorityQueue()
{
	delete [] m_Queue;
};

void PriorityQueue::Insert(c_Action &job)
{
	m_Queue[job.GetPriority()].Insert(job);
};

c_Action PriorityQueue::Remove()
{
	for(short int index = m_Priorities;index >= 0;index--)
	{
		if(!m_Queue[index]->isEmpty())
			return m_Queue[index]->Remove();
	}
	return NULL;

};






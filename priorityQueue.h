#ifndef _PRIORITY_QUEUE_H
#define _PRIORITY_QUEUE_H

class c_Action;

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
	T* Remove();
	
	/*****************************************/
	bool isEmpty()const
	{	return (m_Tail != NULL) ? true : false ;	};


private:
	struct element
	{
		T Data;
		element *next;
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
	
	void Insert(c_Action &job);
	c_Action& Remove();

private:
	Queue <c_Action> *m_Queue;
	short int m_Priorities;
};


#endif

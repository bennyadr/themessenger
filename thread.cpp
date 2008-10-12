#include "thread.h"
#include "action.h"

template <class job,class parameter>
c_Thread<job,parameter>::c_Thread()
	:m_Id(0),
	m_Action(NULL),
	m_Attribute(NULL),
	m_Parameter(NULL),
	m_iReturnValue(0)
{
};

template <class job,class parameter>
c_Thread<job,parameter>::~c_Thread()
{

};

template <class job,class parameter>
void c_Thread<job,parameter>::Start()
{

	int ret_val = pthread_create(&m_Id,m_Attribute,&m_Action->Execute(),m_Parameter);
	if(ret_val != 0)
	{
		throw c_Error_Thread(ret_val,"error creating thread : "); 
	}
};

template <class job,class parameter>
void c_Thread<job,parameter>::AddParameter(const parameter *param)
{
	m_Parameter = param;
};

template <class job,class parameter>
void c_Thread<job,parameter>::Join()
{
	int ret_val = pthread_join(m_Id,(void*)&m_iReturnValue);
	if(ret_val != 0)
	{
		throw c_Error_Thread(ret_val,"error joining thread : ");
	}
	
};

template <class job,class parameter>
void c_Thread<job,parameter>::Cancel()
{
	int ret_val = pthread_cancel(m_Id);
	if(ret_val != 0)
	{
		throw c_Error_Thread(ret_val,"error canceling thread : ");
	}

};	


#ifndef _ACTION_H
#define _ACTION_H

namespace Action
{
class c_Action
{
	public:
		/*****************************************/
		virtual ~c_Action() {};
		/*****************************************/
		unsigned int GetStatus()const
		{	return m_iStatus;	};
		/*****************************************/
		void SetStatus(const unsigned int status)
		{	m_iStatus = status;   };
		/*****************************************/
		unsigned int GetActionType()const
		{	return m_iType;   };
		/*****************************************/
		virtual void Execute() = 0;
		/*****************************************/
		void SetPriority(const unsigned int priority)
		{	m_iPriority = priority;	  }
		/*****************************************/
		unsigned int GetPriority()const
		{	return m_iPriority   };

	protected:
		unsigned int m_iPriority;
		unsigned int m_iStatus;
		unsigned int m_iType;
		
};

enum  ActionStatus 
{
	CREATED = 0,
	DONE,
	PENDING,
	STARTED
};
enum ActionType
{
	LOGIN = 0,
	LOGOUT,
	GETBUDDYLIST,
	SETSTATUS,
	GETSTATUS
};

};


#endif

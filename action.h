#ifndef _ACTION_H
#define _ACTION_H

namespace Action
{
	enum  ActionStatus 
	{
		CREATED = 0,
		DONE,
		PENDING,
		STARTED,
		FAILED
	};
	enum ActionType
	{
		LOGIN = 0,
		LOGOUT,
		GETBUDDYLIST,
		SETSTATUS,
		GETSTATUS
	};
	
	enum Priority
	{
		LOW = 0,
		NORMAL,
		HIGH
	};

	class c_Action
	{
		public:
			/*****************************************/
			c_Action(unsigned int priority = NORMAL , unsigned int status = CREATED) :
				m_iPriority(priority),
				m_iStatus(status)
				{};
			/*****************************************/
			virtual ~c_Action() {};
			/*****************************************/
			unsigned int GetStatus()const
			{	return m_iStatus;	};
			/*****************************************/
			void SetStatus(const unsigned int status)
			{	m_iStatus = status;   };
			/*****************************************/
			virtual void Execute() = 0;
			/*****************************************/
			void SetPriority(const unsigned int priority)
			{	m_iPriority = priority;	  }
			/*****************************************/
			unsigned int GetPriority()const
			{	return m_iPriority;   };
	
		protected:
			unsigned int m_iPriority;
			unsigned int m_iStatus;
			
	};


};


#endif

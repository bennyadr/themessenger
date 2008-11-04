#ifndef _BUDDY_H
#define _BUDDY_H

#include <string>
#include "ypacket.h"

using namespace YPacket;

class c_Buddy
{
public:

	c_Buddy(const string name,const string group,const unsigned int order,const string status = "",
			yahoo_status ystatus = YAHOO_STATUS_OFFLINE)
		:m_iOrder(order),
		m_iGroup(0),
		m_sGroup(group),
		m_sName(name),
		m_sStatus(status),
		m_iYStatus(ystatus),
		m_bisOnline(false),
		m_iIdleTime(0)
	{		};

	~c_Buddy()	{		};


	void SetName(const string name)
	{	m_sName = name;	  };

	const string GetName()const
	{	return m_sName;	  };

	void SetGroup(const string group)
	{	m_sGroup = group;	};

	const string GetGroup()const
	{	return m_sGroup;	};

	unsigned int GetOrder()const
	{	return m_iOrder;	};

	void SetOrder(const unsigned int order)
	{	m_iOrder = order;	};

	void SetYStatus(yahoo_status  status)
	{	m_iYStatus = status;  };

	void SetStatus(const string status)
	{	m_sStatus = status;   };

	yahoo_status GetYahooStatus()const
	{	return m_iYStatus;	};

	void SetOnline(const bool online)
	{	m_bisOnline = online;	};

	bool isOnline()const
	{	return m_bisOnline;	  };

	void SetIddleTime(unsigned int iddle_time)
	{	m_iIdleTime = iddle_time;	};

	unsigned int GetIddleTime()const
	{	return m_iIdleTime;	  };

	void SetGroupNum(unsigned int group)
	{	m_iGroup = group;	};

	unsigned int GetGroupNum()const
	{	return m_iGroup;	};

private:
	unsigned int m_iOrder;
	unsigned int m_iGroup;
	string m_sGroup;
	string m_sName;
	string m_sStatus;
	yahoo_status m_iYStatus;
	bool m_bisOnline;
	unsigned int m_iIdleTime;
};
#endif


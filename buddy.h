#ifndef _BUDDY_H
#define _BUDDY_H

#include <string>
#include "ypacket.h"

using namespace YPacket;

class c_Buddy
{
public:

	c_Buddy(const string &name,const string& group,const unsigned int order,const string status = "",
			const unsigned int ystatus = yahoo_status.YAHOO_STATUS_OFFLINE)
		:m_iOrder(order),
		m_sGroup(group),
		m_sName(name),
		m_sStatus(status),
		m_iYStatus(ystatus)
	{		};

	~c_Buddy()	{		};


	void SetName(const string& name)
	{	m_sName = name;	  };

	string& GetName()const
	{	return m_sName;	  };

	void SetGroup(const string& group)
	{	m_sGroup = group;	};

	string& GetGroup()const
	{	return m_sGroup;	};

	unsigned int GetOrder()const
	{	return m_iOrder;	};

	void SetOrder(const unsigned int order)
	{	m_iOrder = order;	};

	void SetYStatus(yahoo_status  status)
	{	m_iStatus = status;	  };

	yahoo_status GetYahooStatus()const
	{	return m_iStatus;	};


private:
	unsigned int m_iOrder;
	string m_sGroup;
	string m_sName;
	string m_sStatus;
	yahoo_status m_iYStatus;
	bool m_bisOnline;
	unsigned int m_iIdleTime;

};
#endif


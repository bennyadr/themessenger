#include "recvMessage.h"
#include "Interface/yinstance.h"
#include "buddy_list.h"

/***************************************/
/***************************************/
/***********ReceviveMessage*************/
/***************************************/
/***************************************/

c_RecvMessage::c_RecvMessage(c_YPacket &recvpack)
	:m_FromNum(0)
{
	m_cRecvPacket = recvpack;
};

c_RecvMessage::~c_RecvMessage()
{
};

void c_RecvMessage::Execute()
{
	if(m_cRecvPacket.GetService() == YAHOO_SERVICE_MESSAGE)
	{
		unsigned int iterator = 0;
		while(iterator<m_cRecvPacket.GetDataSize()-1)	
		{
			unsigned char key[100];
			unsigned char value[1024];
			memset(key,0,100*sizeof(unsigned char));
			memset(value,0,1024*sizeof(unsigned char));
			iterator = m_cRecvPacket.GetDataPair(key,value);
			int ikey =atoi(reinterpret_cast<const char*>(key));
			switch(ikey)
			{
				case 1:
				case 4:
					m_sFrom = reinterpret_cast<char*>(value);
					break;
				case 14:
					m_sText = reinterpret_cast<char*>(value);
					break;
			}
		}

	}
};

void c_RecvMessage::SetFromNum()
{
	c_YInstance* yinstance = c_YInstance::GetInstance();
	c_BuddyList* buddy_list = yinstance->GetBuddyList();
	for(unsigned int iterator = 0;iterator < buddy_list->GetSize();iterator++)
	{
		if(buddy_list->GetBuddy(iterator))
		{
			if(buddy_list->GetBuddy(iterator)->GetName() == m_sFrom)
			{
				m_FromNum = iterator + buddy_list->GetBuddy(iterator)->GetGroupNum();
				break;
			}
		}
	}

};

const string& c_RecvMessage::GetFrom()const
{
	return m_sFrom;
};

const string& c_RecvMessage::GetText()const
{
	return m_sText;
};

/***************************************/
/***************************************/
/*************ReceiveNotify*************/
/***************************************/
/***************************************/

c_RecvNotify::c_RecvNotify(c_YPacket &notif_pack)
	:m_state(0)
{
	m_cRecvPacket = notif_pack;
};

c_RecvNotify::~c_RecvNotify()
{
};

void c_RecvNotify::Execute()
{
	if(m_cRecvPacket.GetService() ==YAHOO_SERVICE_NOTIFY)
	{
		unsigned int iterator = 0;
		while(iterator<m_cRecvPacket.GetDataSize()-1)	
		{
			unsigned char key[100];
			unsigned char value[1024];
			memset(key,0,100*sizeof(unsigned char));
			memset(value,0,1024*sizeof(unsigned char));
			iterator = m_cRecvPacket.GetDataPair(key,value);
			int ikey =atoi(reinterpret_cast<const char*>(key));
			switch(ikey)
			{
				case 4:
					m_sFrom = reinterpret_cast<char*>(value);
					break;
				case 13:
					m_state = atoi(reinterpret_cast<const char*>(value));
					break;
			}
		}

	}

};

const int c_RecvNotify::GetStateN()const
{
	return m_state;
};

const string& c_RecvNotify::GetFromN()const
{
	return m_sFrom;
};



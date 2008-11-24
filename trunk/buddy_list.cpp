#include "buddy_list.h"
#include <assert.h>
#include <algorithm>
#include "buddy.h"

string c_BuddyList::Status(yahoo_status status)
{
	switch(status)
	{
		case YAHOO_STATUS_CUSTOM:
			return " ";
		case YAHOO_STATUS_AVAILABLE:
			return "Available";
		case YAHOO_STATUS_BRB:
			return "Brb";
		case YAHOO_STATUS_BUSY:
			return "Busy";
		case YAHOO_STATUS_ONVACATION:
			return "OnVacation";
		default:
			return " ";
	}
};

void c_BuddyList::GetBuddyList(c_YPacket& recvpack)
{
	if(recvpack.GetService() == YAHOO_SERVICE_BUDDYLIST)
	{
		unsigned int iterator = 0;
		while(iterator<recvpack.GetDataSize()-1)	
		{
			unsigned char key[100];
			unsigned char value[1024];
			memset(key,0,100*sizeof(unsigned char));
			memset(value,0,1024*sizeof(unsigned char));
			iterator = recvpack.GetDataPair(key,value);
			int ikey =atoi(reinterpret_cast<const char*>(key));
			switch(ikey)
			{
				case 89:
					//username
					break;
				case 58:
					//cookie
					break;
				case 302:
					//check for ignore list
					break;
				case 300:
					//value = 318 means a group will follow
					//value = 319 means a buddy will follow
					break;
				case 65:
					AddGroup(reinterpret_cast<const char*>(value));
					break;
				case 7:
					AddBuddy(reinterpret_cast<const char*>(value));
					break;
			}
		}
	}
};

void c_BuddyList::GetOnlineBuddies(const c_YPacket& recvpack)
{
	if(recvpack.GetService() == YAHOO_SERVICE_BUDDYLIST_ONLINE)
	{
		unsigned int iterator = 0;
		string name = "";
		string message_status = "";
		yahoo_status status = YAHOO_STATUS_AVAILABLE;
		unsigned int iddle_time = 0;
		while(iterator<recvpack.GetDataSize()-1)	
		{
			unsigned char key[100];
			unsigned char value[1024];
			memset(key,0,100*sizeof(unsigned char));
			memset(value,0,1024*sizeof(unsigned char));
			iterator = recvpack.GetDataPair(key,value);
			int ikey =atoi(reinterpret_cast<const char*>(key));
			switch(ikey)
			{
				case 7:
					if(name != "")  //add previously read buddy with status in the list
					{
						if(message_status == "")
							message_status = Status(status);
						AddStatus(name,message_status,status,iddle_time);
					}
					//username
					name = reinterpret_cast<const char*>(value); 
					message_status = "";
					break;
				case 10:
					if(name == "")
						break;
					status = (yahoo_status)atoi(reinterpret_cast<const char*>(value));	
					break;
				case 19:
					if(name == "")
						break;
					message_status = reinterpret_cast<const char*>(value);
					break;
				case 137:
					//iddle time
					if(name == "")
						break;
					iddle_time = atoi(reinterpret_cast<const char*>(value));
					break;
			}
		}
		if(message_status == "")
			message_status = Status(status);
		AddStatus(name,message_status,status,iddle_time);
	}
};

void c_BuddyList::UpdateBuddies(const c_YPacket& recvpack)
{
	if(recvpack.GetService() == YAHOO_SERVICE_UPDATE_STATUS)
	{
		GetOnlineBuddies(recvpack);
	}
	if(recvpack.GetService() == YAHOO_SERVICE_LOGON)
	{
		GetOnlineBuddies(recvpack);
	}
	if(recvpack.GetService() == YAHOO_SERVICE_LOGOFF)
	{
		unsigned int iterator = 0;
		string name = "";
		string message_status = "";
		yahoo_status status = YAHOO_STATUS_AVAILABLE;
		while(iterator<recvpack.GetDataSize()-1)	
		{
			unsigned char key[100];
			unsigned char value[1024];
			memset(key,0,100*sizeof(unsigned char));
			memset(value,0,1024*sizeof(unsigned char));
			iterator = recvpack.GetDataPair(key,value);
			int ikey =atoi(reinterpret_cast<const char*>(key));
			switch(ikey)
			{
				case 7:
					if(name != "")  
					{
						AddStatus(name,string(""),YAHOO_STATUS_OFFLINE,0);
					}
					//username
					name = reinterpret_cast<const char*>(value); 
					break;
				case 10:
					if(name == "")
						break;
					status = (yahoo_status)atoi(reinterpret_cast<const char*>(value));	
					break;
			}
		}
		AddStatus(name,string(""),YAHOO_STATUS_OFFLINE,0);
	}
	if(recvpack.GetService() == YAHOO_SERVICE_PICTURE)
	{
		//get invisible buddies
		unsigned int iterator = 0;
		string name = "";
		yahoo_status status = YAHOO_STATUS_INVISIBLE;
		while(iterator<recvpack.GetDataSize()-1)	
		{
			unsigned char key[100];
			unsigned char value[1024];
			memset(key,0,100*sizeof(unsigned char));
			memset(value,0,1024*sizeof(unsigned char));
			iterator = recvpack.GetDataPair(key,value);
			int ikey =atoi(reinterpret_cast<const char*>(key));
			if(ikey == 4)
			{
				name = reinterpret_cast<const char*>(value); 
				AddStatus(name,"Invisible",status,0);
			}
		}

		
	}

};

void c_BuddyList::AddGroup(const char* group)
{
	delete [] (m_sAddedGroup);	
	int size = strlen(group)+1;
	try
	{
		m_sAddedGroup = new char[size];
	}
	catch(bad_alloc &allocerr)
	{
		for(unsigned int i=0;i<m_aBuddies.size();i++)
		{
			delete m_aBuddies[i];
		}
		throw allocerr;		
	}
	strncpy(m_sAddedGroup,group,size);
	m_iGroup++;
};

void c_BuddyList::AddBuddy(const char* buddy_name)
{
	const string name(buddy_name);
	const string groupname(m_sAddedGroup);

	c_Buddy *buddy = new c_Buddy(name,groupname,m_iNumber);
	buddy->SetGroupNum(m_iGroup);
	m_aBuddies.insert(m_aBuddies.end(),buddy);
	m_iNumber++;
	assert(m_aBuddies.size() == m_iNumber);
};

void c_BuddyList::AddStatus(const string name,const string status_message,yahoo_status status,unsigned int iddle_time = 0)
{
	for(unsigned int i=0;i<GetSize();i++)
	{
		if(m_aBuddies[i]->GetName() == name)
		{
			m_aBuddies[i]->SetStatus(status_message);
			m_aBuddies[i]->SetYStatus(status);
			if(status == YAHOO_STATUS_OFFLINE)
				m_aBuddies[i]->SetOnline(false);
			else	
				m_aBuddies[i]->SetOnline(true);
			m_aBuddies[i]->SetIddleTime(iddle_time);
			break;
		}
	}
};





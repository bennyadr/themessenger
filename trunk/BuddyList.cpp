#include "BuddyList.h"
#include <assert.h>

void c_BuddyList::GetBuddyList(const c_YPacket& recvpack)
{
	if(recvpack.GetService() == YAHOO_SERVICE_BUDDYLIST)
	{
		unsigned int iterator = 0;
		while(iterator<recvpack.GetDataSize())	
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
	else
		throw c_Error_YPacket("GetBuddyList :: invalid buddy packet");

};

//qsort
void c_BuddyList::Sort(SortBy sortmethod)const
{
	//TODO
};

void c_BuddyList::AddGroup(const char* group)
{
	delete [] (m_sAddedGroup);	
	int size = strlen(group)+1;
	m_sAddedGroup = new char[size];
	strncpy(m_sAddedGroup,group,size);
};

void c_BuddyList::AddBuddy(const char* buddy_name)
{
	const string name(buddy_name);
	const string groupname(m_sAddedGroup);

	c_Buddy *buddy = new c_Buddy(name,groupname,m_iNumber);
	m_aBuddies.insert(m_aBuddies.end(),buddy);
	m_iNumber++;
	assert(m_aBuddies.size() == m_iNumber);
};





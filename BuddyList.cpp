#include "BuddyList.h"

c_Buddy& c_BuddyList::operator[](unsigned int number)const
{
	if(number<=m_iNumber)
		return m_aBuddies[number];
	else
		throw number;	
};

void c_BuddyList::GetBuddyList(const c_YPacket& recvpack)
{
	if(recvpack.GetService() == YPacket::yahoo_service.YAHOO_SERVICE_LIST)
	{
		unsigned char key[100];
		unsigned char value[1024];
		recvpack.GetDataPair(&key,&value);
		int ikey =atoi(key);
		switch(ikei)
		{
			case 89:
				//username
				break;
			case 58:
				//cookie
				break;
			case 216:
				//name
				break;
			case 254:
				//surename
				break;
			case 302:
				//check for ignore list
				break;
			case 300:
				//value = 318 means a group will follow
				//value = 319 means a buddy will follow
				break;
			case 65:
				AddGroup(value);
				break;
			case 7:
				AddBuddy(value);
				break;
			default:
				//unknown
		};
	}
	else
		throw c_Error_YPacket("GetBuddyList :: invalid buddy packet");

};

//qsort
void c_BuddyList::Sort(SortBy sortmethod)
{

};

void c_BuddyList::AddGroup(char* group)
{
	delete [] (m_sAddedGroup);	
	int size = strlen(group)+1;
	m_sAddedGroup = new char[size];
	strncpy(m_sAddedGroup,group,size);
};

void c_BuddyList::AddBuddy(char* buddy)
{
	const string name(buddy);
	const tring groupname(m_sAddedGroup);

	c_Buddy &buddy = new c_Buddy(name,groupname,m_iNumber);
	m_aBuddies.Insert(m_aBuddies.end(),buddy);
	assert(m_aBuddies.size() == m_iNumber);
};





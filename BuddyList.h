#ifndef _BUDDYLYST_H
#define _BUDDYLYST_H

#include <vector>
#include "buddy.h"

using namespace std;

enum SortBy
{
	ByName = 0,
	ByTalkedRecently,
	ByStatus,
	ByJoinedRecently
};

class c_BuddyList
{
public:
	c_BuddyList()
		:m_iNumber(0),
		m_sAddedGroup(NULL)
	{		};

	~c_BuddyList()
	{
		for(unsigned int i=0;i<=m_aBuddies.size();i++)
		{
			delete m_aBuddies[i];
		}
	};

	void GetBuddyList(const c_YPacket& recvpack);

	void Sort(SortBy sortmethod)const;

private:
	void AddGroup(const char* group);
	void AddBuddy(const char* buddy);	

private:
	vector<c_Buddy*> m_aBuddies;
	unsigned int m_iNumber;
	char* m_sAddedGroup;

};


#endif



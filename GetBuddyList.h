#include "socket.h"
#include "ypacket.h"
#include "action.h"
#include <list>

class c_GetBuddyList : public c_Action
{
	public:
		c_GetBuddyList();
		~c_GetBuddyList();

		void RetrieveBuddyList(c_YPacket&);

		list<Buddy> *GetBuddyList();


	private:
		struct Buddy
		{
			string m_UserName;
		};
	private:
		list<Buddy> *m_cBuddyList;
};


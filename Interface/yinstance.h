#ifndef _YINSTANCE_H
#define _YINSTANCE_H

#include "../socket.h"
#include "../ypacket.h"
#include "../login.h"
#include "../priorityQueue.h"
#include <QThread>

using namespace YPacket;

//yahoo instance singleton
class c_YInstance : public QThread 
{
	Q_OBJECT

	public:
		static c_YInstance* GetInstance();
		void run();
		void stop();

		void AddAction(c_Action *action);

		void SetUserPass(string username,string password);

		~c_YInstance();

	signals:
		void SetBuddyList(c_BuddyList *buddylist);
		void SetOnlineBuddies(c_BuddyList *buddylist);
		void BuddyQuited();
		void BuddyJoined();
		void NewMessage(string message);

	private:
		c_YInstance();
		

		//not defined
		c_YInstance(const c_YInstance&);
		c_YInstance& operator=(const c_YInstance&);

	private:
		c_Socket m_socket;
		string *m_username;
		string *m_password;
		PriorityQueue *m_PQueue;
		bool m_bConnected;
		c_BuddyList *m_Buddy_list;
		volatile bool m_stopped;
};

#endif


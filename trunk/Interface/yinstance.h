#ifndef _YINSTANCE_H
#define _YINSTANCE_H

#include "../socket.h"
#include "../ypacket.h"
#include "../login.h"
#include "../priorityQueue.h"
#include <QThread>
#include <QString>
#include <QMutex>

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

		QString GetUserName()const;
		const c_Socket *GetSocket()const;

		~c_YInstance();

	signals:
		void SetBuddyList(c_BuddyList *buddylist);
		void SetOnlineBuddies(c_BuddyList *buddylist);
		void BuddyQuited();
		void BuddyJoined();
		void SendText(QString from,QString text);

	private:
		c_YInstance();
		

		//not defined
		c_YInstance(const c_YInstance&);
		c_YInstance& operator=(const c_YInstance&);

	private:
		string *m_username;
		string *m_password;
		PriorityQueue *m_PQueue;
		bool m_bConnected;
		c_BuddyList *m_Buddy_list;
		volatile bool m_stopped;
		c_Socket m_socket;
		QMutex mutex;
};

#endif


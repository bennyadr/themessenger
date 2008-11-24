#ifndef _YINSTANCE_H
#define _YINSTANCE_H

#include "../socket.h"
#include "../ypacket.h"
#include "../ylogin.h"
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
		string GetUserNameSTL()const;
		const c_Socket *GetSocket()const;
		c_BuddyList *GetBuddyList()const;
		int GetId()const 
		{	return m_session_id;	};

		~c_YInstance();

	signals:
		void SetBuddyList(c_BuddyList *buddylist);
		void SetOnlineBuddies(c_BuddyList *buddylist);
		void BuddyQuited();
		void BuddyJoined();
		void SendText(QString from,QString text);
		void RecvText(QString from,QString text);

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
		int m_session_id;
		c_BuddyList *m_Buddy_list;
		volatile bool m_stopped;
		QMutex mutex;
};

#endif


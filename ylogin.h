#ifndef _LOGIN_H
#define _LOGIN_H

#include <string>
#include <list>

#include "ypacket.h"
#include "action.h"
#include "socket.h"
#include "buddy_list.h"

using namespace Action;
using namespace YPacket;
using namespace std;
 
class c_Login : public c_Action
{
	public:
		c_Login(c_Socket* socket,const char* username,const char* password);
		~c_Login();
		void Execute();

		c_BuddyList* GetBuddyList()const
		{	return m_BuddyList;   };
		const c_YPacket& GetLeftPack()const
		{	return m_leftPack;	  };


	private:
		void CreateSendFirstAuthPacket();
		bool RecvAndSendAuthResponse();
		bool CreateAuthResponse(c_YPacket& packet);
		bool SetBuddyList();
		
		//magic shit from pidgin
		inline void MagicShit(unsigned char*,unsigned char *,unsigned char *);

	private:
		c_Socket *m_cSocket;
		char* m_sUsername;
		char* m_sPassword;
		c_BuddyList* m_BuddyList;
		c_YPacket m_leftPack;
};


#endif

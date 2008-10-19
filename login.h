#ifndef _LOGIN_H
#define _LOGIN_H

#include <string>
#include <list>

#include "ypacket.h"
#include "action.h"
#include "socket.h"


using namespace Action;
using namespace YPacket;
using namespace std;
 
class c_Login : public c_Action
{
	public:
		c_Login(c_Socket* socket,char* username,char* password);
		~c_Login();
		void Execute();

	private:
		inline void CreateSendFirstAuthPacket();
		inline void RecvAndSendAuthResponse();
		inline void	CreateAuthResponse(c_YPacket& packet);
		void GetBuddyList();
		void GetBuddies(unsigned char *list_buffer);

		//magic shit
		inline void MagicShit(unsigned char*,unsigned char *,unsigned char *);

	private:
		c_Socket *m_cSocket;
		char* m_sUsername;
		char* m_sPassword;
		list<string> m_cBuddyList;
};


#endif

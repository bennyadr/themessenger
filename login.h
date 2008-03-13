#ifndef _LOGIN_H
#define _LOGIN_H

#include "action.h"
#include "ypacket.h"
#include "socket.h"

using namespace Action;
using namespace YPacket;
 
class c_Login : public c_Action
{
	public:
		c_Login(c_Socket* socket);
		~c_Login();
		void Execute();

	private:
		inline void CreateAuthPacket(char* yahoo_username);
		inline void SendAuthPacket();
		inline void RecvAndSendAuthResponse();
	private:
		c_Socket *m_cSocket;
		c_YPacket *m_cPacket;
};


#endif

#ifndef _LOGIN_H
#define _LOGIN_H

#include "ypacket.h"
#include "action.h"
#include "socket.h"

using namespace Action;
using namespace YPacket;
 
class c_Login : public c_Action
{
	public:
		c_Login(c_Socket* socket,char* username,char* password);
		~c_Login();
		void Execute();

	private:
		inline void CreateAuthPacket();
		inline void SendAuthPacket();
		inline void RecvAndSendAuthResponse();
		void 		CreateAuthResponse();
	private:
		c_Socket *m_cSocket;
		c_YPacket *m_cPacket;
		char* m_sUsername;
		char* m_sPassword;
};


#endif

#ifndef _SENDMESSAGE_H
#define _SENDMESSAGE_H

#include "action.h"
#include "ypacket.h"
#include "socket.h"

using namespace Action;
using namespace YPacket;

class c_SendMessage : public c_Action
{
	public:
	c_SendMessage(const c_Socket *socket,string from,string to,string text,yahoo_status status);
	~c_SendMessage();

	void Execute();

	private:
	string m_sFrom;
	string m_sTo;
	string m_sText;
	const c_Socket *m_cSocket;
	yahoo_status m_status;
};

#endif



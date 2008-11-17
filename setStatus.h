#ifndef _SETSTATUS_H
#define _SETSTATUS_H

#include "action.h"
#include "ypacket.h"
#include "socket.h"

using namespace Action;
using namespace YPacket;

class c_SetStatus : public c_Action
{
public:
	c_SetStatus(const c_Socket *socket,string text,yahoo_status status,int id);
	~c_SetStatus();
	void Execute();

private:
	const c_Socket *m_cSocket;
	string m_sText;
	yahoo_status m_status;
	int m_id;
};




#endif

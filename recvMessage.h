#ifndef _RECVMESSAGE_H
#define _RECVMESSAGE_H

#include "action.h"
#include "ypacket.h"
#include "socket.h"

using namespace Action;
using namespace YPacket;

class c_RecvMessage
{
	public:
		c_RecvMessage(c_YPacket &recvpack);
		~c_RecvMessage();

		void Execute();

		const string& GetFrom()const;
		const string& GetText()const;

		void SetFromNum();

	private:
		c_YPacket m_cRecvPacket;
		string m_sFrom;
		string m_sText;
		unsigned int m_FromNum;
};

#endif


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

		inline void SetFromNum();

	private:
		c_YPacket m_cRecvPacket;
		string m_sFrom;
		string m_sText;
		unsigned int m_FromNum;
};

class c_RecvNotify
{
public:
	c_RecvNotify(c_YPacket &recv_pack);
	~c_RecvNotify();

	const int GetStateN()const;
	const string& GetFromN()const;
	void Execute();

private:
	c_YPacket m_cRecvPacket;
	string m_sFrom;
	int m_state;
};

#endif


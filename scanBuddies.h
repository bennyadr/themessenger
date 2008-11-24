#ifndef _SCANBUDDIES_H
#define _SCANBUDDIES_H


#include "action.h"
#include "ypacket.h"
#include "socket.h"

using namespace Action;
using namespace YPacket;


class c_ScanBuddies : public c_Action
{
public:

	c_ScanBuddies(const c_Socket *socket,int id,string buddy,string username);
	~c_ScanBuddies();

	void Execute();

private:
	void PeerScan();
private:
	int m_id;
	const c_Socket *m_socket;
	string m_buddy;
	string m_username;
};




#endif


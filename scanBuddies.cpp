#include "scanBuddies.h"


c_ScanBuddies::c_ScanBuddies(const c_Socket *socket,int id,string buddy,string username)
	:m_id(id),
	m_socket(socket)
{
	m_buddy = buddy;
	m_username = username;
};


c_ScanBuddies::~c_ScanBuddies()
{
};


void c_ScanBuddies::PeerScan()
{
	c_YPacket sendpack(17+m_buddy.size()+m_username.size(),YAHOO_SERVICE_PICTURE,YAHOO_STATUS_AVAILABLE,m_id);
	unsigned char key[10];
	unsigned char value[100];
	memset(key,0,10);
	memset(value,0,100);
	key[0] = 0x31;
	sendpack.AddDataPair(key,reinterpret_cast<unsigned char*>((char*)m_buddy.c_str()));
	key[0] = 0x35; 
	sendpack.AddDataPair(key,reinterpret_cast<unsigned char*>((char*)m_username.c_str()));
	key[0] = 0x31;
	key[1] = 0x33;	
	value[0] = 0x31;
	sendpack.AddDataPair(key,value);
	m_socket->Write(sendpack);
};

void c_ScanBuddies::Execute()
{
	PeerScan();
};

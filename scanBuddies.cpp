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
	sendpack.AddDataPair(key,reinterpret_cast<unsigned char*>((char*)m_username.c_str()));
	key[0] = 0x35; 
	sendpack.AddDataPair(key,reinterpret_cast<unsigned char*>((char*)m_buddy.c_str()));
	key[0] = 0x31;
	key[1] = 0x33;	
	value[0] = 0x31;
	sendpack.AddDataPair(key,value);
	m_socket->Write(sendpack);

	/*c_YPacket sendpack1(17+m_buddy.size()+m_username.size(),YAHOO_SERVICE_CHAT7,YAHOO_STATUS_AVAILABLE,m_id);
	unsigned char key1[10];
	unsigned char value1[100];
	memset(key1,0,10);
	memset(value1,0,100);
	key1[0] = 0x31;
	sendpack1.AddDataPair(key1,reinterpret_cast<unsigned char*>((char*)m_buddy.c_str()));
	key1[0] = 0x35; 
	sendpack1.AddDataPair(key1,reinterpret_cast<unsigned char*>((char*)m_username.c_str()));
	key1[0] = 0x31;
	key1[1] = 0x33;	
	value1[0] = 0x31;
	sendpack1.AddDataPair(key1,value1);
	m_socket->Write(sendpack1);


	//peertopeer
	c_YPacket sendpack2(17+m_buddy.size()+m_username.size(),YAHOO_SERVICE_PEERTOPEER,YAHOO_STATUS_AVAILABLE,m_id);
	unsigned char key2[10];
	unsigned char value2[100];
	memset(key2,0,10);
	memset(value2,0,100);
	key2[0] = 0x31;
	sendpack2.AddDataPair(key2,reinterpret_cast<unsigned char*>((char*)m_username.c_str()));
	key2[0] = 0x34;
	sendpack2.AddDataPair(key2,reinterpret_cast<unsigned char*>((char*)m_username.c_str()));
	key2[0] = 0x31;
	key2[1] = 0x32;
	sendpack2.AddDataPair(key2,reinterpret_cast<unsigned char*>((char*)"LTYzODYwMzQ1NQ=="));
	key2[0] = 0x36;
	key2[1] = 0x31;
	value2[0] = 0x30;
	sendpack2.AddDataPair(key2,value2);
	key2[0] = 0x32;
	key2[1] = 0;
	value[0] = 0;
	sendpack2.AddDataPair(key2,value2);
	key2[0] = 0x35; 
	sendpack2.AddDataPair(key2,reinterpret_cast<unsigned char*>((char*)m_buddy.c_str()));
	key2[0] = 0x31;
	key2[1] = 0x33;	
	value2[0] = 0x30;
	sendpack2.AddDataPair(key2,value2);
	key2[0] = 0x34;
	key2[1] = 0x39;
	sendpack2.AddDataPair(key2,reinterpret_cast<unsigned char*>((char*)"PEERTOPEER"));
	m_socket->Write(sendpack2);*/


	
};

void c_ScanBuddies::Execute()
{
	PeerScan();
};

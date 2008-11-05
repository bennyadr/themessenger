#include "sendMessage.h"


c_SendMessage::c_SendMessage(const c_Socket *socket,string from,string to,string text,yahoo_status status)
	:m_cSocket(NULL),
	m_status(status)
{
	m_sFrom = from;
	m_sTo = to;
	m_sText = text;
	m_cSocket = socket;
};

c_SendMessage::~c_SendMessage()
{
};

void c_SendMessage::Execute()
{
	int tst_size = m_sFrom.size() + m_sText.size() + m_sTo.size();
	c_YPacket sendpack(55+tst_size,YAHOO_SERVICE_MESSAGE,m_status,0);
	unsigned char key[10];
	unsigned char value[100];
	memset(key,0,10);
	memset(value,0,100);
	key[0] = 0x31;
	sendpack.AddDataPair(key,reinterpret_cast<unsigned char*>((char*)m_sFrom.c_str()));
	key[0] = 0x35; 	
	sendpack.AddDataPair(key,reinterpret_cast<unsigned char*>((char*)m_sTo.c_str()));
	key[0] = 0x39;
	key[1] = 0x37;
	value[0] = 0x31;
	sendpack.AddDataPair(key,value);
	key[0] = 0x31;
	key[1] = 0x34;
	sendpack.AddDataPair(key,reinterpret_cast<unsigned char*>((char*)m_sText.c_str()));
	key[0] = 0x36;
	key[1] = 0x33;
	value[0] = 0x3b;
	value[1] = 0x30;
	sendpack.AddDataPair(key,value);
	key[0] = 0x36;
	key[1] = 0x34;
	value[0] = 0x30;
	value[1] = 0;
	sendpack.AddDataPair(key,value);
	key[0] = 0x31;
	key[1] = 0x30;
	key[2] = 0x30;
	key[3] = 0x32;
	value[0] = 0x31;
	sendpack.AddDataPair(key,value);
	key[0] = 0x32;
	key[1] = 0x30;
	key[2] = 0x36;
	key[3] = 0;
	value[0] = 0x30;
	sendpack.AddDataPair(key,value);
	m_cSocket->Write(sendpack);
};	

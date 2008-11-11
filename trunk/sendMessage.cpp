#include "sendMessage.h"

/***************************************/
/***************************************/
/**************SendMessage**************/
/***************************************/
/***************************************/


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


/***************************************/
/***************************************/
/************SendNotify*****************/
/***************************************/
/***************************************/

c_SendNotify::c_SendNotify(const c_Socket *socket,string from,string to,yahoo_status status,bool on)
	:m_socket(NULL),
	m_status(status),
	m_on(on)
{
	m_sFrom = from;
	m_sTo = to;
	m_socket = socket;
};

c_SendNotify::~c_SendNotify()
{
};

void c_SendNotify::Execute()
{
	int tst_size = m_sFrom.size() + m_sTo.size();
	c_YPacket sendpack(46+tst_size,YAHOO_SERVICE_NOTIFY,m_status,0);
	unsigned char key[10];
	unsigned char value[100];
	unsigned char *notify = (unsigned char*) "TYPING";
	memset(key,0,10);
	memset(value,0,100);
	key[0] = 0x34;
	key[1] = 0x39;
	sendpack.AddDataPair(key,notify);
	key[0] = 0x31; 	
	sendpack.AddDataPair(key,reinterpret_cast<unsigned char*>((char*)m_sFrom.c_str()));
	key[0] = 0x31;
	key[1] = 0x34;
	value[0] = 0x20;
	sendpack.AddDataPair(key,value);
	key[0] = 0x31;
	key[1] = 0x33;
	if(m_on)
		value[0] = 0x31;
	else
		value[0] = 0x30;
	sendpack.AddDataPair(key,value);
	key[0] = 0x35;
	key[1] = 0;
	sendpack.AddDataPair(key,reinterpret_cast<unsigned char*>((char*)m_sTo.c_str()));
	key[0] = 0x31;
	key[1] = 0x30;
	key[2] = 0x30;
	key[3] = 0x32;
	value[0] = 0x31;
	sendpack.AddDataPair(key,value);
	m_socket->Write(sendpack);
};



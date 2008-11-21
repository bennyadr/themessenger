/***************************************/
/***************************************/
/**************SET  STATUS**************/
/***************************************/
/***************************************/


#include "setStatus.h"
#include <cstdlib>

c_SetStatus::c_SetStatus(const c_Socket *socket,string text,yahoo_status status,int id)
	:m_cSocket(socket),
	m_sText(text),
	m_status(status),
	m_id(id)
{

};

c_SetStatus::~c_SetStatus()
{
};

void c_SetStatus::Execute()
{
	if(m_status == YAHOO_STATUS_CUSTOM)
	{
		c_YPacket sendpack(28+m_sText.size(),YAHOO_SERVICE_UPDATE_STATUS,m_status,m_id);
		unsigned char key[10];
		unsigned char value[100];
		memset(key,0,10);
		memset(value,0,100);
		key[0] = 0x31;
		key[1] = 0x30;
		value[0] = 0x39;
		value[1] = 0x39;
		sendpack.AddDataPair(key,value);
		key[0] = 0x39;
		key[1] = 0x37;
		value[0] = 0x31;
		value[1] = 0;
		sendpack.AddDataPair(key,value);
		key[0] = 0x31;
		key[1] = 0x39;
		sendpack.AddDataPair(key,reinterpret_cast<unsigned char*>((char*)m_sText.c_str()));
		if(m_status == YAHOO_STATUS_ONPHONE || m_status == YAHOO_STATUS_BUSY)
		{
			key[0] = 0x34; 	
			key[1] = 0x37;
			value[0] = 0x32;
			value[1] = 0;
			sendpack.AddDataPair(key,value);
		}	
		else
		{	
			key[0] = 0x34; 	
			key[1] = 0x37;
			value[0] = 0x31;
			value[1] = 0;
			sendpack.AddDataPair(key,value);
		}
		m_cSocket->Write(sendpack);

		c_YPacket sendpack1(7,YAHOO_SERVICE_UPDATE_STATUS_INVISIBLE,m_status,m_id);
		unsigned char key1[10];
		unsigned char value1[100];
		memset(key1,0,10);
		memset(value1,0,100);
		key1[0] = 0x31;
		key1[1] = 0x33;
		value1[0] = 0x31;
		sendpack1.AddDataPair(key1,value1);
		m_cSocket->Write(sendpack1);

	}
	else
		if(m_status != YAHOO_STATUS_INVISIBLE)
		{
			c_YPacket sendpack(20,YAHOO_SERVICE_UPDATE_STATUS,m_status,m_id);
			unsigned char key[10];
			unsigned char value[100];
			memset(key,0,10);
			memset(value,0,100);
			key[0] = 0x31;
			key[1] = 0x30;
			snprintf(reinterpret_cast<char*>(value),2,"%d",m_status);
			sendpack.AddDataPair(key,value);
			key[0] = 0x31;
			key[1] = 0x39;
			value[0] = 0;
			sendpack.AddDataPair(key,value);
			key[0] = 0x34; 	
			key[1] = 0x37;
			value[0] = 0x31;
			value[1] = 0;
			sendpack.AddDataPair(key,value);
			m_cSocket->Write(sendpack);

			c_YPacket sendpack1(7,YAHOO_SERVICE_UPDATE_STATUS_INVISIBLE,m_status,m_id);
			unsigned char key1[10];
			unsigned char value1[100];
			memset(key1,0,10);
			memset(value1,0,100);
			key1[0] = 0x31;
			key1[1] = 0x33;
			value1[0] = 0x31;
			sendpack1.AddDataPair(key1,value1);
			m_cSocket->Write(sendpack1);

		}
		else
		{
			c_YPacket sendpack(7,YAHOO_SERVICE_UPDATE_STATUS_INVISIBLE,m_status,m_id);
			unsigned char key[10];
			unsigned char value[100];
			memset(key,0,10);
			memset(value,0,100);
			key[0] = 0x31;
			key[1] = 0x33;
			value[0] = 0x32;
			sendpack.AddDataPair(key,value);
			m_cSocket->Write(sendpack);
		}
};	



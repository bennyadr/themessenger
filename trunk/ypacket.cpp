#include "ypacket.h"
#include "bits.h"
using namespace YPacket;

/*****************************************/

c_YPacket::c_YPacket(const unsigned int size,enum yahoo_service service,enum yahoo_status status,int id)
	:c_Message(size+YAHOO_HEADER_SIZE),
	m_iPriority(0),
	m_bSerialized(false)
{
	m_ypack.size = size;
	m_ypack.service = service;
	m_ypack.status = status;	
	m_ypack.id = id;
	m_ypack.ydata = NULL;
};

/*****************************************/

c_YPacket::c_YPacket(const unsigned int size)
	:c_Message(size+YAHOO_HEADER_SIZE),
	m_iPriority(0),
	m_bSerialized(false)
{
	memset(&m_ypack,0,sizeof(ypacket));
	m_ypack.size = size;
	m_ypack.ydata = NULL;
};

/*****************************************/

c_YPacket::c_YPacket()
	:c_Message(),
	m_iPriority(0),
	m_bSerialized(false),
	m_iByteIterator(0)
{
	memset(&m_ypack,0,sizeof(ypacket));
};

/*****************************************/

/*****************************************/

c_YPacket::~c_YPacket()
{
	if(m_ypack.ydata != NULL)
		delete [] m_ypack.ydata;
};

/*****************************************/

c_YPacket::c_YPacket(const c_YPacket& ypack)
{
	if(m_sBuffer==NULL)
		c_Message::c_Message(ypack.GetDataSize()+YAHOO_HEADER_SIZE);
	else
	{
		delete[] m_sBuffer;
		c_Message::c_Message(ypack.GetDataSize()+YAHOO_HEADER_SIZE);
	}
	m_ypack.size = ypack.GetDataSize();
	m_ypack.service = ypack.GetService();	
	m_ypack.status = ypack.GetStatus();
	m_ypack.id = ypack.GetId();
	if(m_ypack.ydata == NULL)
		m_ypack.ydata = new unsigned char [m_ypack.size];
	else
	{
		delete [] m_ypack.ydata;
		m_ypack.ydata = new unsigned char [m_ypack.size];
	}
	memcpy(m_ypack.ydata,ypack.GetData(),m_ypack.size);
};

/***************************************/

c_YPacket& c_YPacket::operator=(const c_YPacket& ypack)
{
	if(this!=&ypack)
	{
		if(m_sBuffer==NULL)
			c_Message::c_Message(ypack.GetDataSize()+YAHOO_HEADER_SIZE);
		else
		{
			delete[] m_sBuffer;
			c_Message::c_Message(ypack.GetDataSize()+YAHOO_HEADER_SIZE);
		}
		m_ypack.size = ypack.GetDataSize();
		m_ypack.service = ypack.GetService();	
		m_ypack.status = ypack.GetStatus();
		m_ypack.id = ypack.GetId();
		if(m_ypack.ydata == NULL)
			m_ypack.ydata = new unsigned char [m_ypack.size];
		else
		{
			delete [] m_ypack.ydata;
			m_ypack.ydata = new unsigned char [m_ypack.size];
		}
		memcpy(m_ypack.ydata,ypack.GetData(),m_ypack.size);
	}
	return *this; 
};

/*****************************************
 * The DATA part of the yahoo packet is
 * composed of key-value pairs separated
 * by 0xC080
 * !!!Use only one of the following 2 
 * functions for a c_YPacket object 
 * because they share the same iterator
*****************************************/

void c_YPacket::AddDataPair(unsigned char* key,unsigned char* value)
{
	int size = strlen(reinterpret_cast<const char*>(key));
	memcpy(m_ypack.ydata+m_iByteIterator,key,size);
	m_iByteIterator += size;
	Bits::memset_short(m_ypack.ydata+m_iByteIterator,YAHOO_STD_SEPARATOR,2);
	m_iByteIterator += 2;
	int value_size = strlen(reinterpret_cast<const char*>(value));
	memcpy(m_ypack.ydata+m_iByteIterator,value,value_size);
	m_iByteIterator += value_size;
};

unsigned int c_YPacket::GetDataPair(unsigned char* const key,unsigned char* const value)const
{
	bool foundkey = false;
	bool foundvalue = false;
	unsigned int i = 0;
	unsigned int j = 0;
	while( m_iByteIterator < (m_ypack.size-1) && !foundvalue)
	{
		if(Bits::GetUShortInt(m_ypack.ydata+m_iByteIterator) == YAHOO_STD_SEPARATOR)
		{
			m_iByteIterator += 2;
			if(!foundkey)
				foundkey = true;
			else
				foundvalue = true;
		}
		else
		{
			if(!foundkey)
			{
				key[i] = m_ypack.ydata[m_iByteIterator];
				i++;
			}
			else
			{
				value[j] = m_ypack.ydata[m_iByteIterator];
				j++;
			}
			m_iByteIterator++;
		}
	}
	return m_iByteIterator;
};


/*****************************************
*  The packet should be serialized before
*  sending it throw the socket
*****************************************/
void c_YPacket::Serialize()const
{
	m_iSize = m_ypack.size + YAHOO_HEADER_SIZE; 
	delete [] m_sBuffer;
	m_sBuffer = new unsigned char[m_iSize];

	//set protocol name
	Bits::memset_int(m_sBuffer,YAHOO_PROTOCOL,4);
	
	//set yahoo version
	Bits::memset_int(m_sBuffer+4,YAHOO_VERSION,4);
	
	//set message size
	Bits::memset_short(m_sBuffer+8,m_ypack.size,2);

	//set yahoo service type
	Bits::memset_short(m_sBuffer+10,m_ypack.service,2);

	//set yahoo status type
	Bits::memset_int(m_sBuffer+12,m_ypack.status,4);

	//set yahoo id
	Bits::memset_int(m_sBuffer+16,m_ypack.id,4);	

	//set data
	memcpy(m_sBuffer+20,m_ypack.ydata,m_iSize-YAHOO_HEADER_SIZE);
	
	m_bSerialized = true;
};

/*****************************************
 * The byte array string should be 
 * deserialized after it's read from the
 * socket
*****************************************/
void c_YPacket::Deserialize(unsigned char* buffer)
{
	m_ypack.size = GetYPackSize(buffer);
	m_iSize = m_ypack.size+YAHOO_HEADER_SIZE;
	m_ypack.service = Bits::GetUShortInt(buffer+10);
	m_ypack.status = Bits::GetUInt(buffer+12);
	m_ypack.id = Bits::GetUInt(buffer+16);
	m_ypack.ydata = new unsigned char[m_ypack.size+1];
	memset(m_ypack.ydata,0,m_ypack.size+1);
	memcpy(m_ypack.ydata,buffer+YAHOO_HEADER_SIZE,m_ypack.size);
	m_bSerialized = false;
};
void c_YPacket::Clear()
{
	c_Message::Clear();
	m_ypack.size = 0;
	m_ypack.service = 0;
	m_ypack.status = 0;
	m_ypack.id = 0;
	delete [] m_ypack.ydata;
	m_ypack.ydata = NULL;
};



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
	delete [] m_ypack.ydata;

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
	memcpy(m_ypack.ydata+m_iByteIterator,key,strlen(key));
	m_iByteIterator += strlen(key);
	Bits::memset_short(m_ypack.ydata+m_iByteIterator,YAHOO_STD_SEPARATOR,2);
	m_iByteIterator += 2;
	memcpy(m_ypack.ydata+m_iByteIterator,value,strlen(value));
	m_iByteIterator += strlen(value);
};

void c_Ypacket::GetDataPair(unsigned char* const key,unsigned char* const data)const
{
	bool foundkey = false;
	bool foundvalue = false;
	while( m_iByteIterator != m_ypack.size && !foundvalue)
	{
		if(YAHOO_STD_SEPARATOR == reinterpret_cast<short>key[m_iByteIterator])
		{
			m_iByteIterator += 2;
			if(!foudkey)
				foundkey = true;
			else
				foundvalue = true;
		}
		else
		{
			if(!foundkey)
				key[m_iByteIterator] = m_ypack.ydata[m_iByteIterator];
			else
				value[m_iByteIterator] = m_ypack.ydata[m_iByteIterator];
		}
	}
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
	m_ypack.service = (short) m_sBuffer[10];
	m_ypack.status = (unsigned int) m_sBuffer[12];
	m_ypack.id = (unsigned int) m_sBuffer[16];
	m_ypack.ydata = new unsigned char[m_ypack.size+YAHOO_HEADER_SIZE];
	memcpy(m_ypack.ydata,buffer+YAHOO_HEADER_SIZE,m_ypack.size);
	m_bSerialized = false;
};


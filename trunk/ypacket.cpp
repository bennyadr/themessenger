#include "ypacket.h"
#include "bits.h"
using namespace YPacket;

/*****************************************/

c_YPacket::c_YPacket(const unsigned int size,enum yahoo_service service,enum yahoo_status status,int id)
	:c_Message(size),
	m_iPriority(0),
	m_bSerialized(false)
{
	m_ypack.size = size;
	m_ypack.service = service;
	m_ypack.status = status;	
	m_ypack.id = id;
	m_ypack.data = NULL;
};

/*****************************************/

c_YPacket::c_YPacket(const unsigned int size)
	:c_Message(size),
	m_iPriority(0),
	m_bSerialized(false)
{
	memset(m_ypack,0,sizeof(ypacket));
	m_ypack.size = size;
	m_ypack.data = NULL;
};

/*****************************************/

c_YPacket::c_YPacket()
	:c_Message(),
	m_iPriority(0),
	m_bSerialized(false)
{
};

/*****************************************/

c_YPacket::c_YPacket(const c_YPacket& packet)
	:c_Message(packet)
{
	m_iPriority = packet.GetPriority();
	m_bSerialized = packet.isSerialized();
	memcpy(m_ypack,packet.GetPacket(),packet.GetSize());
	if(packet.isSerialized())
	{
		m_sBuffer = new unsigned char[packet.GetSize()];
		memcpy(m_sBuffer,packet.GetBuffer(),packet.GetSize());
	}
};

/*****************************************/

const c_YPacket& c_YPacket::operator=(const c_YPacket& packet)
{
	if( this != &packet )
	{
		delete [] m_sBuffer;
		m_iSize=packet.GetSize();
		m_sBuffer = new unsigned char[m_iSize];
		memcpy(m_sBuffer,packet.GetBuffer(),m_iSize);
	}
	return *this;
};

/*****************************************/

c_YPacket::~c_YPacket()
{
	delete [] m_ypack.ydata;

};

/*****************************************/

void c_YPacket::Serialize()
{
	//set protocol name
	Bits::memset_int(m_sBuffer,YAHOO_PROTOCOL,4);
	
	//set yahoo version
	Bits::memset_int(m_sBuffer+4,YAHOO_VERSION,4);
	
	//set message size
	unsigned short packet_size = m_ypack.size - YAHOO_HEADER_SIZE;
	Bits::memset_short(m_sBuffer+8,packet_size,2);

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

/*****************************************/

void c_YPacket::Deserialize(unsigned char* buffer)
{
	m_ypack.size = (short) m_sBuffer[8];
	m_ypack.service = (short) m_sBuffer[10];
	m_ypack.status = (unsigned int) m_sBuffer[12];
	m_ypack.id = (unsigned int) m_sBuffer[16];
	m_ypack.ydata = m_sBuffer[20];
	m_bSerialized = false;
	
};


#include "ypacket.h"
#include "bits.h"
using namespace YPacket;

/*****************************************/

c_YPacket::c_YPacket(const unsigned int size,enum yahoo_service service,enum yahoo_status status,int id)
	:c_Message(size),
	m_iPriority(0)
{
	//set protocol name
	Bits::memset_int(m_sBuffer,YAHOO_PROTOCOL,4);
	
	//set yahoo version
	Bits::memset_int(m_sBuffer+4,YAHOO_VERSION,4);
	
	//set message size
	unsigned short packet_size = size - YAHOO_HEADER_SIZE;
	Bits::memset_short(m_sBuffer+8,packet_size,2);

	//set yahoo service type
	Bits::memset_short(m_sBuffer+10,service,2);

	//set yahoo status type
	Bits::memset_int(m_sBuffer+12,status,4);

	//set yahoo id
	Bits::memset_int(m_sBuffer+16,id,4);	
	
	m_sData = m_sBuffer + YAHOO_HEADER_SIZE;
};

c_YPacket::c_YPacket(const unsigned int size)
:c_Message(size),
m_iPriority(0)
{
	m_sData = m_sBuffer + YAHOO_HEADER_SIZE;
};

/*****************************************/

c_YPacket::c_YPacket(const c_YPacket& packet)
	:c_Message(packet)
{
	m_iPriority = packet.GetPriority();
	m_sData = packet.GetData();
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

void c_YPacket::SetData(const unsigned char *data,unsigned int data_size)
{
	memcpy(m_sData,data,data_size);
};

/*****************************************/

c_YPacket::~c_YPacket()
{

};

/*****************************************/


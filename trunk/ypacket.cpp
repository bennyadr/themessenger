#include "ypacket.h"

using namespace YPacket;

/*****************************************/

c_YPacket::c_YPacket(const unsigned int size)
	:c_Message(size),
	m_iPriority(0)
{
	m_sData = m_sBuffer + 20*sizeof(char);
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
c_YPacket::~c_YPacket()
{

};





#include "ypingtime.h"
#include "ypacket.h"


c_PingTimer::c_PingTimer(int seconds,c_Socket *socket)
	:m_time(0),
	m_seconds(seconds),
	m_socket(socket)
{
	time(&m_time);
};

c_PingTimer::~c_PingTimer()
{
};

void c_PingTimer::SendPing()
{
	time_t now;
	now = time(&now);
	if((now - m_time) > m_seconds)
	{
		c_YPacket pingpack(0,YAHOO_SERVICE_PING,YAHOO_STATUS_AVAILABLE,0);
		m_socket->Write(pingpack);
		m_time = now;
	}
};


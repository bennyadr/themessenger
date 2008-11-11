#ifndef _YPINGTIME_H
#define _YPINGTIME_H

#include <time.h>
#include "socket.h"


class c_PingTimer
{
public:
	c_PingTimer(int seconds,c_Socket *socket);
	~c_PingTimer();

	void SendPing();

private:
	time_t m_time;
	int m_seconds;
	c_Socket *m_socket;

};

#endif


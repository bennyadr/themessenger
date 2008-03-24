#include "socket.h"
#include "ypacket.h"
#include "login.h"
using namespace YPacket;

int main()
{
	c_Socket socket;
	try
	{
		socket.Connect();
		c_Login login(&socket,"mileandrei","t1h2o3r4i5u6m72455");
 		login.Execute();
	
	}
	catch(c_Error_Socket &socket_error)
	{
		socket_error.PrintError();
	}

	return 1;
};


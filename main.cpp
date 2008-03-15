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
		c_Login login(&socket,"mileandrei","thorium");
		login.Execute();
	
	}
	catch(c_Error_Socket &socket_error)
	{
		socket_error.PrintError();
	}

	return 1;
};


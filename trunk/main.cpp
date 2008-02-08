#include "socket.h"
#include "ypacket.h"

using namespace YPacket;

int main()
{
	c_Socket socket;
	try
	{
		socket.Connect();
		string andrei("dsadsada");
		socket.Write(andrei);// for testing
		c_YPacket packet1(20);
		socket.Write(packet1);
	}
	catch(c_Error_Socket &socket_error)
	{
		socket_error.PrintError();
	}
	return 1;
};


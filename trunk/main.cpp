#include "socket.h"



int main()
{
	c_Socket socket;
	try
	{
		socket.Connect();
		socket.Write("stuff!!");// for testing
	}
	catch(c_Error_Socket &socket_error)
	{
		socket_error.PrintError();
	}
	return 1;
};


#include "socket.h"
#include "ypacket.h"
#include "login.h"
using namespace YPacket;
/*******************************************/
//We have the following states :
//-wait 0
//-command 1
//-processing 2
/*******************************************/
int main()
{
	int state = 0;
	state = IGetState();

	if(a)
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
	}
	if(login.GetStatus() == DONE)
	{
	 	
	}
		
	};

	return 1;
};


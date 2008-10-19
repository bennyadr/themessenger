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
	c_Socket socket;
	try
	{
		socket.Connect();
		c_Login login(&socket,"mileandrei","t1h2o3r4i5u6m72455");
 		login.Execute();

		if(login.GetStatus() == DONE)
		{
			cout<<"finished login\n";	 	
		}
	}
	catch(c_Error_Socket &socket_error)
	{
		cout<<"eroare cu socketi\n";
		socket_error.PrintError();
	}
		
	return 1;
};


#ifndef _SOCKET_H
#define _SOCKET_H


/*****************************************
 * 				c_Socket
 * Description : Socket class implementation 
 * Methods:
 *		-Connect 
 *		-Write
 *		-Read
 *		-Close
 *		-is_Opened ->returns if the connection is active
 *
 *****************************************
 * 			c_Error_Socket
 * Description : Socket error class implementation
 * Methods : 
 * 		-Print ->print error message
 *
 *
*****************************************/

#include <iostream>
#include <string>
#include "unix_std_space.h"
#include "config.h"

using namespace unix_std_space;
using namespace std;
using namespace config;

class c_Socket
{
public:
	 c_Socket();
	~c_Socket();

	void Connect();
	void Write(const string& message,const int flag);
	int Read(string &message,const int flag);
	bool is_Opened()const
				{ return m_bStatus;	};



private:
	unsigned int m_iPort;
	string *m_sAddress ;
	int m_iSocketFd;
	sockaddr_in m_tAddress;
	bool m_bStatus;

	
};


class c_Error_Socket
{
public:
	c_Error_Socket(int ret,const string& user_message)
	{
		if(ret<0)
		{
			const char *a=strerror(errno);
			m_sErrorMessage = new string(a);
			m_sUserMessage = new string(user_message);
		}
		else
		{
			m_sErrorMessage = new string("--");
			m_sUserMessage = new string(user_message);
		}
	};

	~c_Error_Socket()
	{
		delete(m_sErrorMessage);
	};
	
	void PrintError()
	{
		cout<<"Error message :: "<<*m_sUserMessage<<*m_sErrorMessage<<endl;
	};

private:
	int m_iReturnValue;
	string *m_sErrorMessage;
	string *m_sUserMessage;


};

#endif

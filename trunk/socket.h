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
#include "message_base.h"

using namespace unix_std_space;
using namespace std;
using namespace config;


class c_Socket
{
public:
	 c_Socket();
	~c_Socket();

	void Connect();
	void Disconnect();
	void Write(const string& message);
	void Read(string& message,const unsigned int count);
	void Write(const string& message,const int flag);
	void Read(string &message,const unsigned int count,const int flag);
	void Write(const c_Message& );
	void Read(c_Message& ,const unsigned int count);
	void Write(const c_Message& ,const int flag);
	void Read(c_Message& ,const unsigned int count,const int flag);

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
		m_sUserMessage = new string(user_message);
		if(ret<0)
		{
			m_sErrorMessage = new string(strerror(errno));
					}
		else
		{
			m_sErrorMessage = new string("");
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
	string *m_sErrorMessage;
	string *m_sUserMessage;


};

#endif

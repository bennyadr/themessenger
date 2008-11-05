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
#include "ypacket.h"

using namespace unix_std_space;
using namespace std;
using namespace config;

#define WARNING 1
#define ERROR 2

using namespace YPacket;

class c_Socket
{
public:
	 c_Socket();
	virtual ~c_Socket();

	virtual	void Connect();
	void Disconnect();

	void MakeBlocking();
	void MakeNonBlocking();

	void Write(const c_Message& message )const;
	void Send(const c_Message& ,const int flag);

	void Write(const c_YPacket& data)const;

	void Read(c_Message& message,const unsigned int count);
	void Recv(c_Message& message,const unsigned int count,const int flag);
	
	void Read(c_YPacket& packet);
	void Recv(c_YPacket& packet,const int flag);

	bool ReadNonBlocking(c_YPacket& packet);

	bool is_Opened()const
				{ return m_bStatus;	};
	

private:
	bool isAvailableData()const;
	void Select();

private:
	unsigned int m_iPort;
	string m_sAddress ;
	int m_iSocketFd;
	sockaddr_in m_tAddress;
	bool m_bStatus;

	
};


class c_Error_Socket
{
public:
	c_Error_Socket(int ret,const string user_message,int type = ERROR)
		:m_iType(type)
	{
		m_sUserMessage = string(user_message);
		if(ret<0)
		{
			m_sErrorMessage = string(strerror(errno));
		}
		else
		{
			m_sErrorMessage = "";
		}
	};

	~c_Error_Socket()
	{
	};
	
	void PrintError()
	{
		if(m_sErrorMessage != "")
		{	
			cout<<"Error message :: "<<m_sUserMessage<<m_sErrorMessage<<endl;
		}
		else
		{
			cout<<"Error message :: "<<m_sUserMessage;
		}
	};

	string& GetErrorMessage()
	{
		m_sUserMessage = m_sUserMessage + m_sErrorMessage + "\n";
		return  m_sUserMessage;
	};
	
	int GetType()const
	{
		return m_iType;
	};

private:
	int m_iType;
	string m_sErrorMessage;
	string m_sUserMessage;


};

#endif

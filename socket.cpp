#include "socket.h"

/*****************************************/

c_Socket::c_Socket()
	:m_iPort(PORT),
 	m_iSocketFd(-1)
 {
 	m_sAddress = new string(SERVER_ADDRESS);
	memset( &m_tAddress , 0 , sizeof(m_tAddress) );
	m_bStatus = false;
};

/*****************************************/

c_Socket::~c_Socket()
{
	delete(m_sAddress);
};

/*****************************************/

void c_Socket::Connect()
{
	m_iSocketFd=socket(AF_INET,SOCK_STREAM,0);
	if(m_iSocketFd==-1)
		throw c_Error_Socket(m_iSocketFd , "error creating socket : ");

	m_tAddress.sin_family = AF_INET;
	m_tAddress.sin_addr.s_addr = INADDR_ANY;
	m_tAddress.sin_port = htons ( m_iPort );

        int on = 1;
	setsockopt(m_iSocketFd,IPPROTO_TCP,SO_REUSEADDR, &on, sizeof(on));

	int status = inet_pton ( AF_INET, m_sAddress->c_str(), &m_tAddress.sin_addr );



	if(status<0)
		throw c_Error_Socket(status , "error creating network address structure : ");
	if(status<1)
		throw c_Error_Socket(status , "error creating network address structure : invalid address ");
	
	status = connect ( m_iSocketFd , (sockaddr *) &m_tAddress, sizeof(m_tAddress) );
	if(status==-1)
		throw c_Error_Socket(status, "error connecting socket : ");
	
	m_bStatus = true;

};

/*****************************************/

void c_Socket::Disconnect()
{
	if(is_Opened())
	{
		int close_ret = close(m_iSocketFd);
	if(close_ret == -1)
		throw c_Error_Socket(close_ret, "error closing socket : ");
	}
};

/*****************************************/

void c_Socket::Write(const c_Message *data)
{
	int ret_write = write(m_iSocketFd,data->GetBuffer(),data->GetSize());
	if(ret_write==-1)
		throw c_Error_Socket(ret_write,"error sending data : ");

};

/*****************************************/

void c_Socket::Write(const c_Message& data)
{
	int ret_write = write(m_iSocketFd,data.GetBuffer(),data.GetSize());
	if(ret_write==-1)
		throw c_Error_Socket(ret_write,"error sending data : ");

};

/*****************************************/

void c_Socket::Send(const c_Message* data,const int flag)
{
	int ret_write = send(m_iSocketFd,data->GetBuffer(),data->GetSize(),flag);
	if(ret_write==-1)
		throw c_Error_Socket(ret_write,"error sending data : ");
};

/*****************************************/

void c_Socket::Send(const c_Message& data,const int flag)
{
	int ret_write = send(m_iSocketFd,data.GetBuffer(),data.GetSize(),flag);
	if(ret_write==-1)
		throw c_Error_Socket(ret_write,"error sending data : ");
};

/*****************************************/

void c_Socket::Read(c_Message& data,const unsigned int count)
{
	char buffer[count];
	int ret_read=read(m_iSocketFd,buffer,count);
	if (ret_read==-1)
		throw c_Error_Socket(ret_read,"error reading data");
	data = buffer;
};

/*****************************************/

void c_Socket::Recv(c_Message &data,const unsigned int count,const int flag)
{
	char buffer[count];
	int ret_recv = recv(m_iSocketFd,buffer,count,flag);
	if(ret_recv==-1)
		throw c_Error_Socket(ret_recv, "error receiving data");
	data = buffer;
};

/*****************************************/





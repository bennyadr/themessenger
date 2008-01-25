#include "socket.h"

/*****************************************/

c_Socket::c_Socket()
{
	m_iPort = PORT;
	m_sAddress = new string(SERVER_ADDRESS);
 	m_iSocketFd = -1;
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

	int bind_ret = bind( m_iSocketFd , (struct sockaddr *) &m_tAddress , sizeof(m_tAddress) );
	if(bind_ret==-1)
		throw c_Error_Socket(bind_ret , "error binding socket : ");


	int status = inet_pton ( AF_INET, m_sAddress->c_str(), &m_tAddress.sin_addr );
	if(status<1)
		throw c_Error_Socket(status , "error creating network address structure : ");

    status = connect ( m_iSocketFd , (sockaddr *) &m_tAddress, sizeof(m_tAddress) );
	if(status==-1)
		throw c_Error_Socket(status, "error connecting socket : ");
	
	m_bStatus = true;

};

/*****************************************/

void c_Socket::Write(const string &data,const int flag)
{
	int ret_send = send(m_iSocketFd,data.c_str(),data.size(),flag);
	if(ret_send==-1)
		throw c_Error_Socket(ret_send, "error sending data : ");
	
};

/*****************************************/

int c_Socket::Read(string &data,const int flag)
{
	/*
	char* buffer;
	buffer = 
	int ret_recv = recv(data);
	if(ret_recv==-1)
		throw c_Error_Socket(ret_recv, "error receiving data");*/
	return 1;
};

/*****************************************/





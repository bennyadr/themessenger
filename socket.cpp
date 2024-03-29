#include "socket.h"
#include "bits.h"
#include <assert.h>


/*****************************************/
/*****************************************/
/*****************************************/
/*          Unix based socket            */
/*****************************************/
/*****************************************/
/*****************************************/

#ifndef WINDOWS


/*****************************************/

c_Socket::c_Socket()
	:m_iPort(PORT),
 	m_iSocketFd(-1)
 {
 	m_sAddress = string(SERVER_ADDRESS);
	memset( &m_tAddress , 0 , sizeof(m_tAddress) );
	m_bStatus = false;
};

/*****************************************/

c_Socket::~c_Socket()
{
	if(is_Opened())
	{
		close(m_iSocketFd);
	}
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

	struct timeval tv;
	tv.tv_sec = 5;
	tv.tv_usec = 0;

	int retsockopt = setsockopt(m_iSocketFd,SOL_SOCKET,SO_RCVTIMEO,(char*)&tv,sizeof(tv));
	if(retsockopt < 0)
		throw c_Error_Socket(retsockopt,"error setting socket timeout : ");

	int status = inet_pton ( AF_INET, m_sAddress.c_str(), &m_tAddress.sin_addr );
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

void c_Socket::Disconnect()const
{
	if(is_Opened())
	{
		int close_ret = close(m_iSocketFd);
	if(close_ret == -1)
		throw c_Error_Socket(close_ret, "error closing socket : ");
	}
	m_bStatus = false;
};

/*****************************************/

void c_Socket::MakeBlocking()
{
	int O_BLOCK = ~ O_NONBLOCK;
	int ret = fcntl(m_iSocketFd,F_SETFL,O_BLOCK);
	if(ret == -1)
		throw c_Error_Socket(ret,"error makeing socket blocking : ");
};

/*****************************************/

void c_Socket::MakeNonBlocking()
{
	int ret = fcntl(m_iSocketFd,F_SETFL,O_NONBLOCK);
	if(ret == -1)
		throw c_Error_Socket(ret,"error makeing socket non-blocking : ");
};

/*****************************************/

void c_Socket::Write(const c_Message& data)const
{
	int ret_write = write(m_iSocketFd,data.GetBuffer(),data.GetSize());
	if(ret_write==-1)
		throw c_Error_Socket(ret_write,"error sending data : ");

};


/*****************************************/

void c_Socket::Write(const c_YPacket& data)const
{
	if(!data.isSerialized())
	{
		data.Serialize();
	}
	int ret_write = write(m_iSocketFd,data.GetBuffer(),data.GetSize());
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
	data.SetBuffer(reinterpret_cast<unsigned char*>(buffer),ret_read);
};

/*****************************************/

void c_Socket::Recv(c_Message &data,const unsigned int count,const int flag)
{
	char buffer[count];
	int ret_recv = recv(m_iSocketFd,buffer,count,flag);
	if(ret_recv==-1)
		throw c_Error_Socket(ret_recv, "error receiving data");
	data.SetBuffer(reinterpret_cast<unsigned char*>(buffer),ret_recv);
};

/*****************************************/

void c_Socket::Recv(c_YPacket& packet,const int flag)
{
	unsigned char buffer[20];
	int ret_recv = recv(m_iSocketFd,buffer,20,flag);
	if(ret_recv<=0)
		throw c_Error_Socket(ret_recv,"error receiving data");
	unsigned short size = GetYPackSize(buffer);
	char buffer_1[size+20];
	memcpy(buffer_1,buffer,20);
	ret_recv = recv(m_iSocketFd,(buffer_1+20),size,flag);
	if(ret_recv<=0)
		throw c_Error_Socket(ret_recv,"error receiving data");
	packet.Deserialize(reinterpret_cast<unsigned char*>(buffer_1));	
}

/*****************************************/

void c_Socket::Read(c_YPacket& packet)
{
	unsigned char buffer[20];
	int ret_read = read(m_iSocketFd,buffer,20);
	if(ret_read<=0)
		throw c_Error_Socket(ret_read,"error receiving data");
	if(0 != strncmp(reinterpret_cast<const char*>(buffer),"YMSG",4))
	{
		throw c_Error_Socket(1,"wrong yahoo packet");
	}
	unsigned short size = GetYPackSize(buffer);
	char buffer_1[size+YAHOO_HEADER_SIZE];
	memcpy(buffer_1,buffer,YAHOO_HEADER_SIZE);
	int offset = YAHOO_HEADER_SIZE;
	while(size>0)
	{
		ret_read = read(m_iSocketFd,(buffer_1+offset),size);
		if(ret_read<0)
			throw c_Error_Socket(ret_read,"error receiving data");
		size -= ret_read;
		offset += ret_read;
	}
	assert(size==0);
	packet.Deserialize(reinterpret_cast<unsigned char*>(buffer_1));	
};

/*****************************************/

bool c_Socket::ReadNonBlocking(c_YPacket& packet)
{
	unsigned char buffer[20];
	int ret_read = read(m_iSocketFd,buffer,20);
	if(ret_read < 0)
	{
		if(errno == EWOULDBLOCK)
			return false;
		else
			throw c_Error_Socket(ret_read,"error reading from non-blocking socket : ");
	};
	if(0 != strncmp(reinterpret_cast<const char*>(buffer),"YMSG",4))
	{
		//throw c_Error_Socket(1,"wrong yahoo packet");
		return false;
	}
	unsigned short size = GetYPackSize(buffer);
	char buffer_1[size+YAHOO_HEADER_SIZE];
	memcpy(buffer_1,buffer,YAHOO_HEADER_SIZE);
	int offset = YAHOO_HEADER_SIZE;
	while(size>0)
	{
		ret_read = read(m_iSocketFd,(buffer_1+offset),size);
		if(ret_read<0)
			throw c_Error_Socket(ret_read,"error receiving data");
		size -= ret_read;
		offset += ret_read;
	}
	assert(size==0);
	packet.Deserialize(reinterpret_cast<unsigned char*>(buffer_1));	
	return true;
};

#endif

/*****************************************/
/*****************************************/
/*****************************************/
/*       Windows based socket            */
/*****************************************/
/*****************************************/
/*****************************************/

#ifdef WINDOWS


/*****************************************/

c_Socket::c_Socket()
	:m_iPort(PORT),
 	m_iSocketFd(-1)
 {
 	m_sAddress = string(SERVER_ADDRESS);
	memset( &m_tAddress , 0 , sizeof(m_tAddress) );
	m_bStatus = false;

	//initialize socket
	WORD wVersionRequested;
    WSADATA wsaData;
	wVersionRequested = MAKEWORD(1, 1);
	int err = WSAStartup(wVersionRequested, &wsaData);
	if(err != 0)
		throw c_Error_Socket(1 , "error requesting socket version ");
};

/*****************************************/

c_Socket::~c_Socket()
{
	WSACleanup();
};

/*****************************************/

void c_Socket::Connect()
{
	m_iSocketFd=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	if(m_iSocketFd == INVALID_SOCKET)
		throw c_Error_Socket(m_iSocketFd , "error creating socket : ");

	m_tAddress.sin_family = AF_INET;
	m_tAddress.sin_addr.s_addr = INADDR_ANY;
	m_tAddress.sin_port = htons ( m_iPort );
	//m_tAddress.sin_addr.S_un.S_addr = inet_addr(m_sAddress.c_str());
	m_tAddress.sin_addr.s_addr = inet_addr(m_sAddress.c_str());

	int status = connect ( m_iSocketFd , (sockaddr *) &m_tAddress, sizeof(m_tAddress) );
	if(status == SOCKET_ERROR)
		throw c_Error_Socket(status, "error connecting socket : ");
	
	m_bStatus = true;

};

/*****************************************/

void c_Socket::Disconnect()const
{
	if(is_Opened())
	{
		int close_ret = closesocket(m_iSocketFd);
	if(close_ret == SOCKET_ERROR)
		throw c_Error_Socket(close_ret, "error closing socket : ");
	}
	m_bStatus = false;
};

/*****************************************/

void c_Socket::MakeBlocking()
{
	u_long iMode = 0;
	int ret = ioctlsocket(m_iSocketFd,FIONBIO,&iMode);
	if(ret == SOCKET_ERROR)
		throw c_Error_Socket(ret,"error makeing socket blocking : ");
};

/*****************************************/

void c_Socket::MakeNonBlocking()
{
	u_long iMode = 1;
	int ret = ioctlsocket(m_iSocketFd,FIONBIO,&iMode);
	if(ret == SOCKET_ERROR)
		throw c_Error_Socket(ret,"error makeing socket non-blocking : ");
};

/*****************************************/

void c_Socket::Write(const c_YPacket& data)const
{
	if(!data.isSerialized())
	{
		data.Serialize();
	}
	int ret_write = send(m_iSocketFd,reinterpret_cast<char*>(data.GetBuffer()),data.GetSize(),0);
	if(ret_write == SOCKET_ERROR)
		throw c_Error_Socket(ret_write,"error sending data : ");
};

/*****************************************/

void c_Socket::Read(c_YPacket& packet)
{
	unsigned char buffer[20];
	int ret_read = recv(m_iSocketFd,reinterpret_cast<char*>(buffer),20,0);
	if(ret_read <= 0)
		throw c_Error_Socket(ret_read,"error receiving data");
	if(0 != strncmp(reinterpret_cast<const char*>(buffer),"YMSG",4))
	{
		throw c_Error_Socket(1,"wrong yahoo packet");
	}
	unsigned short size = GetYPackSize(buffer);
	char buffer_1[size+YAHOO_HEADER_SIZE];
	memcpy(buffer_1,buffer,YAHOO_HEADER_SIZE);
	int offset = YAHOO_HEADER_SIZE;
	while(size>0)
	{
		ret_read = recv(m_iSocketFd,reinterpret_cast<char*>(buffer_1+offset),size,0);
		if(ret_read <= 0)
			throw c_Error_Socket(ret_read,"error receiving data");
		size -= ret_read;
		offset += ret_read;
	}
	assert(size==0);
	packet.Deserialize(reinterpret_cast<unsigned char*>(buffer_1));	
};

/*****************************************/

bool c_Socket::ReadNonBlocking(c_YPacket& packet)
{
	unsigned char buffer[20];
	int ret_read = recv(m_iSocketFd,reinterpret_cast<char*>(buffer),20,0);
	if(ret_read <= 0)
	{
		if(WSAGetLastError() == WSAEWOULDBLOCK)
			return false;
		else
			throw c_Error_Socket(ret_read,"error reading from non-blocking socket : ");
	};
	if(0 != strncmp(reinterpret_cast<const char*>(buffer),"YMSG",4))
	{
		throw c_Error_Socket(1,"wrong yahoo packet");
	}
	unsigned short size = GetYPackSize(buffer);
	char buffer_1[size+YAHOO_HEADER_SIZE];
	memcpy(buffer_1,buffer,YAHOO_HEADER_SIZE);
	int offset = YAHOO_HEADER_SIZE;
	while(size>0)
	{
		ret_read = recv(m_iSocketFd,reinterpret_cast<char*>(buffer_1+offset),size,0);
		if(ret_read <= 0)
		{
			if(WSAGetLastError() == WSAEWOULDBLOCK)
				return false;
			else
				throw c_Error_Socket(ret_read,"error reading from non-blocking socket : ");
		};
		size -= ret_read;
		offset += ret_read;
	}
	assert(size==0);
	packet.Deserialize(reinterpret_cast<unsigned char*>(buffer_1));	
	return true;
};


#endif



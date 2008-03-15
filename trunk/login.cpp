#include "login.h"
#include "bits.h"
c_Login::c_Login(c_Socket *socket,char* username,char* password)
	:m_cSocket(socket),
	m_cPacket(NULL)
{
	m_sUsername = strdup(username);
	m_sPassword = strdup(password);
	
};

c_Login::~c_Login()
{
	delete (m_cPacket);
};

void c_Login::CreateAuthPacket()
{

	unsigned int user_name_size = strlen(m_sUsername);
	m_cPacket = new c_YPacket(35,YAHOO_SERVICE_AUTH,YAHOO_STATUS_AVAILABLE,0);
	
	unsigned char data[14];

	//add first 1 byte -- pidgin style :)
	memset(data,0x31,1);
	//add separator
	Bits::memset_short(data+1,YAHOO_STD_SEPARATOR,2);

	//add username
	memcpy(data+3,m_sUsername,user_name_size);

	//add separator
	Bits::memset_short(data+3+user_name_size,YAHOO_STD_SEPARATOR,2);	

	m_cPacket->SetData(data,15);
	
};

void c_Login::SendAuthPacket()
{
	if(m_cSocket->is_Opened())
	{
		
		m_cSocket->Write(m_cPacket);
	}
};
void c_Login::RecvAndSendAuthResponse()
{
	c_YPacket receive_packet(117);
	m_cSocket->Read(receive_packet,117);
	
	//debug	
	//receive_packet.PrintAsHex();
	//m_cSocket->Write(receive_packet);

	

};

void c_Login::Execute()
{
	CreateAuthPacket();
	m_cPacket->PrintAsHex();
	SendAuthPacket();
	RecvAndSendAuthResponse();
}	

#include "login.h"
#include "ypacket.h"
#include "bits.h"
c_Login::c_Login(c_Socket *socket)
	:m_cSocket(socket),
	m_cPacket(NULL)
{
	
};

c_Login::~c_Login()
{
	delete (m_cPacket);
};

void c_Login::CreateAuthPacket(char* yahoo_username)
{

	unsigned int user_name_size = strlen(yahoo_username);
	m_cPacket = new c_YPacket(35,YAHOO_SERVICE_AUTH,YAHOO_STATUS_AVAILABLE,0);
	
	unsigned char data[14];

	//add first 1 byte -- pidgin style :)
	memset(data,0x31,1);
	//add separator
	Bits::memset_short(data+1,YAHOO_STD_SEPARATOR,2);

	//add username
	memcpy(data+3,yahoo_username,user_name_size);

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
	c_YPacket receive_packet(120);
	m_cSocket->Read(receive_packet,120);
	m_cSocket->Write(receive_packet);

};

void c_Login::Execute()
{
	CreateAuthPacket("mileandrei");
	m_cPacket->PrintAsHex();
	SendAuthPacket();
	RecvAndSendAuthResponse();
}	

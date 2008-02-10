#include "login.h"

using namespace Action;

/*****************************************/
c_Login::c_Login():
	m_cSocket(NULL),
	m_cPacket(NULL)
{
	m_iStatus = CREATED;
	m_iType = LOGIN;

};

c_Login::~c_Login()
{

};

void c_Login::CreateLoginPacket()
{

};

void c_Login::SendPacket()
{

};

void c_Login::Execute()
{

};

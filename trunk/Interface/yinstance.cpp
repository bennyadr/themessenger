#include "yinstance.h"
#include "../sendMessage.h"
#include "../recvMessage.h"
#include "../ypingtime.h"
#include "../ylog.h"

c_YInstance::c_YInstance()
	:m_username(NULL),
	m_password(NULL),
	m_PQueue(NULL),
	m_bConnected(false),
	m_session_id(0),
	m_Buddy_list(NULL),
	m_stopped(false)
{
		m_PQueue = new PriorityQueue(3);
};

c_YInstance::~c_YInstance()
{
	stop();
	wait();
	delete m_username;
	delete m_password;
	delete m_Buddy_list;
	delete m_PQueue;
};

void c_YInstance::run()
{
	m_stopped = false;
	c_YPacket y_pack;
	try
	{
		m_socket.Connect();	
		c_Login *login = new c_Login(&m_socket,m_username->c_str(),m_password->c_str());
	   	login->Execute();
		if(login->GetStatus() == DONE)
		{
			c_Log logger("Login successfull");
			m_bConnected = true;			
			m_Buddy_list = login->GetBuddyList(); 
			emit SetBuddyList(m_Buddy_list);
			y_pack = login->GetLeftPack();
			m_session_id = y_pack.GetId();
			//get online buddies
			if(y_pack.GetService() == YAHOO_SERVICE_BUDDYLIST_ONLINE)
			{
				m_Buddy_list->GetOnlineBuddies(y_pack);
				emit SetOnlineBuddies(m_Buddy_list);
				c_Log loggerlist("List successfull");
			}
		}
		else
		{
			c_Log logger("invalid Login");
			delete login;
			login = NULL;
			QString error = "Error";
			QString error_message = "Invalid username or password.Please try again...";
			emit SendText(error,error_message);
			m_socket.Disconnect();
			return;
		}

		delete login;
		login = NULL;
	}
	catch(c_Error_Socket &error)
	{
		c_Log logger("socket error");
		QString error_message = QString::fromStdString(error.GetErrorMessage());	
		QString error = "Error";
		emit SendText(error,error_message);
		try
		{
			m_socket.Disconnect();
		}
		catch(c_Error_Socket &error)
		{
			QString error_message1 = QString::fromStdString(error.GetErrorMessage());	
			QString error1 = "Error";
			emit SendText(error1,error_message1);
		}
		return;
	}
	catch(bad_alloc)
	{
		QString error_message = "error allocating memmory\n";
		QString error = "Error";
		emit SendText(error,error_message);
		return;
	}
	
	m_socket.MakeNonBlocking();
	
	//start ping timer --ping every 30 sec
	c_PingTimer pingtimer(30,&m_socket);

	while(!m_stopped)			
	{
		try
		{	
			pingtimer.SendPing();			
			//process user actions
			mutex.lock();
			if(!m_PQueue->isEmpty())
			{
				c_Action* action = m_PQueue->Remove();
				mutex.unlock();
				c_SendMessage *sendmess_act = dynamic_cast<c_SendMessage*>(action);
				if(sendmess_act)
				{
					c_Log logger("send message!");
					sendmess_act->Execute();
					delete sendmess_act;
					continue;
				}
				c_SendNotify *sendnotif_act = dynamic_cast<c_SendNotify*>(action);
				if(sendnotif_act)
				{
					c_Log logger("send notify!");
					sendnotif_act->Execute();
					delete(sendnotif_act);
					continue;
				}
			}
			mutex.unlock();

			//process incoming messages from the server
			if(!m_socket.ReadNonBlocking(y_pack))
				continue;

			//get online buddies
			if(y_pack.GetService() == YAHOO_SERVICE_BUDDYLIST_ONLINE)
			{
				m_Buddy_list->GetOnlineBuddies(y_pack);
				emit SetOnlineBuddies(m_Buddy_list);
			}
			if(y_pack.GetService() == YAHOO_SERVICE_UPDATE_STATUS || y_pack.GetService() == YAHOO_SERVICE_LOGON || y_pack.GetService() == YAHOO_SERVICE_LOGOFF)
			{
				m_Buddy_list->UpdateBuddies(y_pack);
				emit SetOnlineBuddies(m_Buddy_list);
				c_Log logger("updated list");
			}
			//handle received message
			if(y_pack.GetService() == YAHOO_SERVICE_MESSAGE)
			{
				c_RecvMessage receive_mess(y_pack);
				receive_mess.Execute();
				QString from(QString::fromStdString(receive_mess.GetFrom()));
				QString text(QString::fromStdString(receive_mess.GetText()));
				emit RecvText(from,text);	
				c_Log logger("receive message!");

			};
			if(y_pack.GetService() == YAHOO_SERVICE_NOTIFY)
			{
				c_RecvNotify receive_notif(y_pack);
				receive_notif.Execute();
				QString from(QString::fromStdString(receive_notif.GetFromN()));
				if(receive_notif.GetStateN() == 1)
				{
					QString typing("Notify");
					emit RecvText(from,typing);	
					c_Log logger("received notify");
				}
				else
				{
					QString typing("Notify_end");
					emit RecvText(from,typing);	
					c_Log logger("received notify");
				}
			}
			y_pack.Clear();
		}
		catch(c_Error_Socket &error)
		{
			c_Log logger("socket error");
			QString error_message = QString::fromStdString(error.GetErrorMessage());	
			QString error = "Error";
			emit SendText(error,error_message);
			try
			{
				m_socket.Disconnect();
			}
			catch(c_Error_Socket &error)
			{
				QString error_message1 = QString::fromStdString(error.GetErrorMessage());	
				QString error1 = "Error";
				emit SendText(error1,error_message1);
			}
			return;
		}
		catch(bad_alloc)
		{
			QString error_message = "error allocating memmory\n";
			QString error = "Error";
			emit SendText(error,error_message);
		}
	}
	
};

void c_YInstance::AddAction(c_Action *action)
{
	mutex.lock();
	m_PQueue->Insert(action);	
	mutex.unlock();
};
void c_YInstance::SetUserPass(string username,string password)	
{
	if(m_username == NULL && m_password == NULL)
	{	
		m_username = new string(username);
		m_password = new string (password);
	}
	else
	{
		delete m_username;
		delete m_password;
		m_username = new string(username);
		m_password = new string (password);
	}
};

QString c_YInstance::GetUserName()const
{
	return QString::fromStdString(*m_username);
};

const c_Socket* c_YInstance::GetSocket()const
{
	return &m_socket;
};

c_BuddyList* c_YInstance::GetBuddyList()const
{
	return m_Buddy_list;
};

c_YInstance* c_YInstance::GetInstance()
{
	static c_YInstance instance;
	return &instance;
};

void c_YInstance::stop()
{
	m_stopped = true;
};


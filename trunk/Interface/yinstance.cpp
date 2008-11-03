#include "yinstance.h"


c_YInstance::c_YInstance()
	:m_username(NULL),
	m_password(NULL),
	m_PQueue(NULL),
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
	try
	{
		m_socket.Connect();	
		c_Login *login = new c_Login(&m_socket,m_username->c_str(),m_password->c_str());
	   	login->Execute();
		c_YPacket y_pack; 
		if(login->GetStatus() == DONE)
		{
			m_bConnected = true;			
			m_Buddy_list = login->GetBuddyList(); 
			emit SetBuddyList(m_Buddy_list);
			y_pack = login->GetLeftPack();
			//get online buddies
			if(y_pack.GetService() == YAHOO_SERVICE_BUDDYLIST_ONLINE)
			{
				m_Buddy_list->GetOnlineBuddies(y_pack);
				emit SetOnlineBuddies(m_Buddy_list);
			}
			m_socket.MakeNonBlocking();
		}
		else
		{
			delete login;
			return;
		}

		delete login;
	}
	catch()
		while(!m_stopped)			
		{
				
			//process incoming messages from the server
			if(!m_socket.ReadNonBlocking(y_pack))
				continue;

			//get online buddies
			if(y_pack.GetService() == YAHOO_SERVICE_BUDDYLIST_ONLINE)
			{
				m_Buddy_list->GetOnlineBuddies(y_pack);
				emit SetOnlineBuddies(m_Buddy_list);
			}
			
			//process user actions
			//mutex here TODO
			if(!m_PQueue->isEmpty())
			{
				c_Action* action = m_PQueue->Remove();
				//mutex end
			//action.Execute();
			}
			//mutex here	

			y_pack.Clear();
		}

	}
	catch(...)
	{
		cout<<"probleme";
	}
};

void c_YInstance::AddAction(c_Action *action)
{
	//mutex here
	m_PQueue->Insert(action);	
	//mutex here
};
void c_YInstance::SetUserPass(string username,string password)	
{
	if(m_username == NULL && m_password == NULL)
	{	
		m_username = new string(username);
		m_password = new string (password);
	}
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


#include "yinstance.h"


c_YInstance::c_YInstance()
	:m_username(NULL),
	m_password(NULL),
	m_PQueue(NULL),
	m_Buddy_list(NULL)
{
		m_PQueue = new PriorityQueue(3);
};

c_YInstance::~c_YInstance()
{
	delete m_username;
	delete m_password;
	delete m_Buddy_list;
	delete m_PQueue;
};

void c_YInstance::run()
{
	try
	{
		cout<<"kkt";
		m_socket.Connect();	
		c_Login login(&m_socket,m_username->c_str(),m_password->c_str());
	/*	login.Execute();
		if(login.GetStatus() == DONE)
		{
			m_bConnected = true;			
			m_Buddy_list = login.GetBuddyList(); 
		}
		
		/*while(true)			
		{
			//process user actions
			//mutex here TODO
			if(!m_PQueue->isEmpty())
			{
				c_Action* action = m_PQueue->Remove();
				//mutex end
			//	action.Execute();
			}
			//mutex here	
			
			//process incoming messages from the server
			c_YPacket y_pack;
			m_socket.MakeNonBlocking();
			if(m_socket.ReadNonBlocking(y_pack));
				break;

			//get online buddies
			
			if(y_pack.GetService() == YAHOO_SERVICE_BUDDYLIST_ONLINE)
			{
				m_Buddy_list->GetOnlineBuddies(y_pack);
			}
			//handle different packets --TODO
	
		}*/

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

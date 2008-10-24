#ifndef _YPACKET_H
#define _YPACKET_H

#include "message_base.h"
#include "bits.h"
namespace YPacket
{

#define YAHOO_STD_SEPARATOR 0xC080
#define YAHOO_VERSION 0x000F0000
#define YAHOO_HEADER_SIZE 20
#define YAHOO_PROTOCOL 0x594D5347


/*****************************************
 *YAHOO SERVICES
*****************************************/
enum yahoo_service 
{ /* these are easier to see in hex */
	YAHOO_SERVICE_LOGON = 1,
	YAHOO_SERVICE_LOGOFF,
	YAHOO_SERVICE_ISAWAY,
	YAHOO_SERVICE_ISBACK,
	YAHOO_SERVICE_IDLE, /* 5 (placemarker) */
	YAHOO_SERVICE_MESSAGE,
	YAHOO_SERVICE_IDACT,
	YAHOO_SERVICE_IDDEACT,
	YAHOO_SERVICE_MAILSTAT,
	YAHOO_SERVICE_USERSTAT, /* 0xa */
	YAHOO_SERVICE_NEWMAIL,
	YAHOO_SERVICE_CHATINVITE,
	YAHOO_SERVICE_CALENDAR,
	YAHOO_SERVICE_NEWPERSONALMAIL,
	YAHOO_SERVICE_NEWCONTACT,
	YAHOO_SERVICE_ADDIDENT, /* 0x10 */
	YAHOO_SERVICE_ADDIGNORE,
	YAHOO_SERVICE_PING,
	YAHOO_SERVICE_GOTGROUPRENAME, /* < 1, 36(old), 37(new) */
	YAHOO_SERVICE_SYSMESSAGE = 0x14,
	YAHOO_SERVICE_PASSTHROUGH2 = 0x16,
	YAHOO_SERVICE_CONFINVITE = 0x18,
	YAHOO_SERVICE_CONFLOGON,
	YAHOO_SERVICE_CONFDECLINE,
	YAHOO_SERVICE_CONFLOGOFF,
	YAHOO_SERVICE_CONFADDINVITE,
	YAHOO_SERVICE_CONFMSG,
	YAHOO_SERVICE_CHATLOGON,
	YAHOO_SERVICE_CHATLOGOFF,
	YAHOO_SERVICE_CHATMSG = 0x20,
	YAHOO_SERVICE_GAMELOGON = 0x28,
	YAHOO_SERVICE_GAMELOGOFF,
	YAHOO_SERVICE_GAMEMSG = 0x2a,
	YAHOO_SERVICE_FILETRANSFER = 0x46,
	YAHOO_SERVICE_VOICECHAT = 0x4A,
	YAHOO_SERVICE_NOTIFY,
	YAHOO_SERVICE_VERIFY,
	YAHOO_SERVICE_P2PFILEXFER,
	YAHOO_SERVICE_PEERTOPEER = 0x4F,	/* Checks if P2P possible */
	YAHOO_SERVICE_WEBCAM,
	YAHOO_SERVICE_AUTHRESP = 0x54,
	YAHOO_SERVICE_LIST,
	YAHOO_SERVICE_AUTH = 0x57,
	YAHOO_SERVICE_ADDBUDDY = 0x83,
	YAHOO_SERVICE_REMBUDDY,
	YAHOO_SERVICE_IGNORECONTACT,	/* > 1, 7, 13 < 1, 66, 13, 0*/
	YAHOO_SERVICE_REJECTCONTACT,
	YAHOO_SERVICE_GROUPRENAME = 0x89, /* > 1, 65(new), 66(0), 67(old) */
	YAHOO_SERVICE_CHATONLINE = 0x96, /* > 109(id), 1, 6(abcde) < 0,1*/
	YAHOO_SERVICE_CHATGOTO,
	YAHOO_SERVICE_CHATJOIN,	/* > 1 104-room 129-1600326591 62-2 */
	YAHOO_SERVICE_CHATLEAVE,
	YAHOO_SERVICE_CHATEXIT = 0x9b,
	YAHOO_SERVICE_CHATLOGOUT = 0xa0,
	YAHOO_SERVICE_CHATPING,
	YAHOO_SERVICE_COMMENT = 0xa8,
	YAHOO_SERVICE_BUDDYLIST = 0xf1,
	YAHOO_SERVICE_BUDDYLIST_ONLINE = 0xf0
};

//yahoo status
enum yahoo_status {
	YAHOO_STATUS_AVAILABLE = 0,
	YAHOO_STATUS_BRB,
	YAHOO_STATUS_BUSY,
	YAHOO_STATUS_NOTATHOME,
	YAHOO_STATUS_NOTATDESK,
	YAHOO_STATUS_NOTINOFFICE,
	YAHOO_STATUS_ONPHONE,
	YAHOO_STATUS_ONVACATION,
	YAHOO_STATUS_OUTTOLUNCH,
	YAHOO_STATUS_STEPPEDOUT,
	YAHOO_STATUS_INVISIBLE = 12,
	YAHOO_STATUS_CUSTOM = 99,
	YAHOO_STATUS_IDLE = 999,
	YAHOO_STATUS_OFFLINE = 0x5a55aa56, /* don't ask */
	YAHOO_STATUS_NOTIFY = 0x16
};

typedef struct ypack
{
	unsigned int size;
	unsigned short service;
	unsigned int status;
	unsigned int id;
	unsigned char* ydata;
} ypacket;

inline unsigned short GetYPackSize(unsigned char *buffer)
{
	return Bits::GetUShortInt(buffer+8);
};

class  c_YPacket : public c_Message
{
	public:
		c_YPacket(const unsigned int size,enum yahoo_service,enum yahoo_status,int id);
		c_YPacket(const unsigned int size);
		c_YPacket();
		virtual ~c_YPacket();

		void Clear();
	
		void SetData(unsigned char* data) 
		{	m_ypack.ydata = reinterpret_cast<unsigned char*> (strdup( reinterpret_cast<const char*>(data) ));	};

		unsigned char* GetData()const
		{	return m_ypack.ydata;   };

		unsigned int GetDataSize()const
		{	return m_ypack.size;	};

		void AddDataPair(unsigned char* key,unsigned char* value);

		unsigned int GetDataPair(unsigned char* key,unsigned char* value)const; 

		void Serialize()const;

		void Deserialize(unsigned char* buffer);

		const bool isSerialized()const
		{	return m_bSerialized;	};

		void SetPriority(const unsigned int priority)
		{	m_iPriority = priority;	 };

		unsigned int GetPriority()const
		{	return m_iPriority;   };

		unsigned short GetService()const
		{	return m_ypack.service;   };

		unsigned int GetStatus()const
		{	return m_ypack.status;   };

		unsigned int GetId()const
		{	return m_ypack.id;   };


	private:
		unsigned int m_iPriority ;
		ypacket m_ypack;
		mutable bool m_bSerialized;
		mutable unsigned int m_iByteIterator;

 
};

class c_Error_YPacket
{
public:
	c_Error_YPacket(const string& user_message)
	{
		m_sUserMessage = new string(user_message);
	};

	~c_Error_YPacket()
	{
		delete(m_sUserMessage);
	};
	
	void PrintError()
	{
		cout<<"Error message :: YPacket error"<<*m_sUserMessage<<endl;
	};

private:
	string *m_sUserMessage;
};

};



#endif


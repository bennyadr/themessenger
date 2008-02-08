#ifndef _YPACKET_H
#define _YPACKET_H

#include "message_base.h"

namespace YPacket
{

class  c_YPacket : public c_Message
{
	public:
		c_YPacket(const unsigned int);
		c_YPacket(const c_YPacket&);
		virtual ~c_YPacket();
		void SetPriority(const unsigned int priority)
		{	m_iPriority = priority;	 };
		unsigned int GetPriority()const
		{	return m_iPriority;   };
		unsigned char* GetData()const
		{	return m_sData;   };  

		const c_YPacket& operator=(const c_YPacket&);

	private:
		unsigned int m_iPriority ;
		unsigned char* m_sData;
 
};


/*****************************************
 *YAHOO SERVICES
*****************************************/

#define 	YAHOO_SERVICE_LOGON            = 0x01
#define 	YAHOO_SERVICE_LOGOFF		   = 0x02
#define 	YAHOO_SERVICE_ISAWAY		   = 0x03
#define 	YAHOO_SERVICE_ISBACK           = 0x04
#define 	YAHOO_SERVICE_IDLE             = 0x05
#define	 	YAHOO_SERVICE_MESSAGE		   = 0x06	 
#define 	YAHOO_SERVICE_IDACT			   = 0x07
#define 	YAHOO_SERVICE_IDDEACT		   = 0x08
#define 	YAHOO_SERVICE_MAILSTAT		   = 0x09
#define     YAHOO_SERVICE_USERSTAT         = 0x0a
#define     YAHOO_SERVICE_NEWMAIL
#define     YAHOO_SERVICE_CHATINVITE
#define     YAHOO_SERVICE_CALENDAR
#define     YAHOO_SERVICE_NEWPERSONALMAIL
#define     YAHOO_SERVICE_NEWCONTACT       = 0x0f
#define     YAHOO_SERVICE_ADDIDENT         = 0x10
#define     YAHOO_SERVICE_ADDIGNORE
#define     YAHOO_SERVICE_PING
#define     YAHOO_SERVICE_GROUPRENAME
#define     YAHOO_SERVICE_SYSMESSAGE       = 0x14
#define     YAHOO_SERVICE_PASSTHROUGH2     = 0x16
#define     YAHOO_SERVICE_CONFINVITE       = 0x18
#define     YAHOO_SERVICE_CONFLOGON
#define     YAHOO_SERVICE_CONFDECLINE      = 0x1a
#define     YAHOO_SERVICE_CONFLOGOFF
#define     YAHOO_SERVICE_CONFADDINVITE
#define     YAHOO_SERVICE_CONFMSG
#define     YAHOO_SERVICE_CHATLOGON
#define     YAHOO_SERVICE_CHATLOGOFF       = 0x1f
#define     YAHOO_SERVICE_CHATMSG          = 0x20
#define     YAHOO_SERVICE_GAMELOGON        = 0x28
#define     YAHOO_SERVICE_GAMELOGOFF
#define     YAHOO_SERVICE_GAMEMSG          = 0x2a
#define     YAHOO_SERVICE_FILETRANSFER     = 0x46
#define     YAHOO_SERVICE_VOICECHAT        = 0x4a
#define     YAHOO_SERVICE_NOTIFY           = 0x4b
#define     YAHOO_SERVICE_P2PFILEXFER      = 0x4d
#define     YAHOO_SERVICE_PEERTOPEER       = 0x4f
#define     YAHOO_SERVICE_AUTHRESP         = 0x54
#define     YAHOO_SERVICE_LIST             = 0x55
#define     YAHOO_SERVICE_AUTH             = 0x57
#define     YAHOO_SERVICE_ADDBUDDY         = 0x83
#define     YAHOO_SERVICE_REMBUDDY         = 0x84
#define     YAHOO_SERVICE_IGNORECONTACT    = 0x85
#define     YAHOO_SERVICE_REJECTCONTACT    = 0x86

}



#endif


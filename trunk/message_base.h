#ifndef _MESSAGE_BASE_H
#define _MESSAGE_BASE_H

#include <string.h>
#include <iostream>
  
using namespace std;

class c_Message
{
	public:

		/*****************************************/

		c_Message(const unsigned int sz)
		:m_iSize(sz)
		{
			m_sBuffer = new  unsigned char[m_iSize];
		};
	
		/*****************************************/

		c_Message(char* message)
		{
			m_iSize = strlen(message);
			m_sBuffer = new unsigned char[m_iSize];
			memcpy(m_sBuffer,message,m_iSize);
		};

		/*****************************************/
	 	
		c_Message(const c_Message &ms)
		{
			m_iSize = ms.GetSize();
			m_sBuffer = new unsigned char[m_iSize];
			memcpy(m_sBuffer,ms.GetBuffer(),m_iSize);
		};

		/*****************************************/
 
		const c_Message& operator=(const c_Message& msg)
		{
			if( this != &msg )
			{
				delete [] m_sBuffer;
				m_iSize=msg.GetSize();
				m_sBuffer = new unsigned char[m_iSize];
				memcpy(m_sBuffer,msg.GetBuffer(),m_iSize);
			}
			return *this;
		};

		/*****************************************/

		const c_Message& operator=(const char* msg)
		{
			delete [] m_sBuffer;
			m_iSize=strlen(msg);
			m_sBuffer = new unsigned char[m_iSize];
			memcpy(m_sBuffer,msg,m_iSize);
			return *this;
		
		};

		/*****************************************/
 
		virtual ~c_Message()
		{
			delete [] m_sBuffer;
		};

		/*****************************************/

		inline unsigned char* GetBuffer()const
			{	return m_sBuffer;	};

		/*****************************************/

		inline unsigned int GetSize()const
			{	return m_iSize;	};

		/*****************************************/

		virtual void PrintAsString()
		{
			cout<<m_sBuffer<<endl;
		};

		/*****************************************/
		
		virtual void PrintAsHex()
		{
			cout.setf( ios_base::hex );
			cout<<m_sBuffer<<endl;
		};

		/*****************************************/

		void Clear()
		{
			memset(m_sBuffer,0,m_iSize);
		};

		/*****************************************/

		virtual bool operator==(const c_Message &msg)
		{
			if( this == &msg )
				return true;
			if(memcmp(m_sBuffer,msg.GetBuffer(),m_iSize))
				return true;
			else
				return false;
				
		};

		/*****************************************/


	protected:
		unsigned char* m_sBuffer;
		unsigned int m_iSize;
};



#endif

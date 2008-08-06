#ifndef _THREAD_H
#define _THREAD_H

#include <pthread.h>
class c_Action; 


/*****************************************
 * Wrapper class for the Posix Thread
*****************************************/
template <class job,class parameter>
class c_Thread
{
public:
	c_Thread();
	~c_Thread();
	void Start();
	void AddParameter(const parameter *param);
	void Join();
	void Cancel();

private:
	pthread_t m_Id;
	job *m_Action;
	parameter* m_Parameter;

	//TODO 
	pthread_attr_t* m_Attribute;

	int m_iReturnValue;


};

/*****************************************
 * Class used for throwing thread
 * specific errors
*****************************************/
class c_Error_Thread
{
public:
	c_Error_Thread(int ret,const string& user_message)
	{
		m_sUserMessage = new string(user_message);
		if(ret<0)
		{
			m_sErrorMessage = new string(strerror(errno));
					}
		else
		{
			m_sErrorMessage = new string("");
		}
	};

	~c_Error_Thread()
	{
		delete(m_sErrorMessage);
	};
	
	void PrintError()
	{
		cout<<"Error message :: "<<*m_sUserMessage<<*m_sErrorMessage<<endl;
	};

private:
	string *m_sErrorMessage;
	string *m_sUserMessage;


};


#endif


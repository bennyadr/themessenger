#ifndef _YLOG_H
#define _YLOG_H

#define LOGFILE "log.txt"

#include <string>

using namespace std;

class c_Log
{
public:
	c_Log(string message);	
	~c_Log();

private:
	string GetTime();

};

#endif


#include "ylog.h"
#include <time.h>
#include <fstream>

c_Log::c_Log(string message)
{
	ofstream logfile;
	logfile.open(LOGFILE,std::ios::app);	
	logfile<<GetTime()<<" : "<<message<<endl;
	logfile.close();
};

c_Log::~c_Log()
{
};


string c_Log::GetTime()
{
	time_t time_str;	
	time(&time_str);
	return string(ctime(&time_str));
};

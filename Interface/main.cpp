#include <QApplication>
#include "FeelerGui.h"
#include "../thread_pool.h"

int main(int argc , char** argv)
{
	QApplication mainApp(argc,argv);
	FeelerGui *gui = new FeelerGui;
	gui->show();

	//process actions
	c_ThreadPool ThreadPool;
	ThreadPool.Process();
	
	return mainApp.exec();
};



#include <QApplication>
#include "FeelerGui.h"
#include "../yinstance.h"

int main(int argc , char** argv)
{
	QApplication mainApp(argc,argv);
	FeelerGui *gui = new FeelerGui;
	gui->show();
	return mainApp.exec();
};



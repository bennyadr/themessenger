#include <QApplication>
#include "FeelerGui.h"

int main(int argc , char** argv)
{
	QApplication mainApp(argc,argv);
	FeelerGui gui;
	gui.show();
	return mainApp.exec();
};



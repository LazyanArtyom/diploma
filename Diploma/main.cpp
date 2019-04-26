#include <QtWidgets/QApplication>

// Local includes
#include "MainWIndow.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	CMainWindow oMain;
	oMain.show();
		
	return a.exec();
}
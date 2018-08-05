#include <QtWidgets/QApplication>
#include <QMessageBox>
#include "MainWIndow.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	
	MainWIndow main;
	main.show();

	return a.exec();
}

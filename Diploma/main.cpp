#include <QtWidgets/QApplication>
#include <QMessageBox>
#include "MainWIndow.h"
#include <QMap>
#include <QtMath>
#include "Histogram.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	
	MainWIndow main;
	main.show();
		
	return a.exec();
}

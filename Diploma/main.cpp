#include "Diploma.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Diploma w;
	w.show();
	return a.exec();
}

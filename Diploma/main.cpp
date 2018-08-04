#include <QtWidgets/QApplication>
#include <QMessageBox>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	QMessageBox box;
	box.setText("Hello world");
	box.show();

	return a.exec();
}

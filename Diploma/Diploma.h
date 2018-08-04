#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Diploma.h"

class Diploma : public QMainWindow
{
	Q_OBJECT

public:
	Diploma(QWidget *parent = Q_NULLPTR);

private:
	Ui::DiplomaClass ui;
};

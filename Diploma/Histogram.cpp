#include "Histogram.h"

Histogram::Histogram(QWidget *pParent) : QWidget(pParent)
{
	resize(60, 60);
	setStyleSheet("background-color: red; border: 3px solid black;");
}

Histogram::~Histogram()
{
}

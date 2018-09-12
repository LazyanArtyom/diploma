#include "HistogramPaneWidget.h"
#include <QGridLayout>

HistogramPaneWidget::HistogramPaneWidget(QWidget *parent)
	: QWidget(parent)
{
	QGridLayout *pLayout = new QGridLayout();
	setLayout(pLayout);
	//setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

	QVector<int> vect = { 5, 5, 5, 5, 5, 5, 5,5, 5, 5, 5,5, 7, 20, 20, 11, 11, 11, 12 };
	QVector<int> vect2 = { 5, 5, 5, 5, 5, 5, 5,5, 5, 5, 5,5, 7, 20, 20, 11, 11, 11, 12 };
	QVector<int> vect3 = { 5, 5, 5, 5, 5, 5, 5,5, 5, 5, 5,5, 7, 20, 20, 11, 11, 11, 12 };
	QVector<int> vect4 = { 5, 5, 5, 5, 5, 5, 5,5, 5, 5, 5,5, 7, 20, 20, 11, 11, 11, 12 };
	QVector<int> vect5 = { 5, 5, 5, 5, 5, 5, 5,5, 5, 5, 5,5, 7, 20, 20, 11, 11, 11, 12 };

	pLayout->addWidget(new CHistogram(vect), 0, 0);
	pLayout->addWidget(new CHistogram(vect2), 0, 1);
	pLayout->addWidget(new CHistogram(vect3), 1, 0);
	pLayout->addWidget(new CHistogram(vect4), 1, 1);
	pLayout->addWidget(new CHistogram(vect5));
}

HistogramPaneWidget::~HistogramPaneWidget()
{
}

#include "HistogramPaneWidget.h"
#include <QGridLayout>

HistogramPaneWidget::HistogramPaneWidget(QWidget *parent)
	: QScrollArea(parent)
{
	QGridLayout *pLayout = new QGridLayout();
	setLayout(pLayout);
	//setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

	QVector<int> vect = { 5, 5, 5, 5, 5, 5, 5,5, 5, 5, 5,5, 7, 20, 20, 11, 11, 11, 12 };

	pLayout->addWidget(new CHistogram(vect), 0, 0);
}

HistogramPaneWidget::~HistogramPaneWidget()
{
}

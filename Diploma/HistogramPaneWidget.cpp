#include "HistogramPaneWidget.h"
#include <QGridLayout>

HistogramPaneWidget::HistogramPaneWidget(QWidget *parent)
	: QWidget(parent)
{
	QGridLayout *pLayout = new QGridLayout();
	setLayout(pLayout);
	//setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

	QVector<int> vect = { 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 7, 12 };

	pLayout->addWidget(new CHistogram(vect));
}

HistogramPaneWidget::~HistogramPaneWidget()
{
}

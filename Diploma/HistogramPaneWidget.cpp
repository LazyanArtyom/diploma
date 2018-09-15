#include "HistogramPaneWidget.h"
#include <QGridLayout>
#include <QScrollBar>

HistogramPaneWidget::HistogramPaneWidget(QWidget *pParent)
	: QWidget(pParent)
{
	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	QGridLayout *pLayout = new QGridLayout();
	setLayout(pLayout);

	pLayout->setSizeConstraint(QLayout::SetMinimumSize);

	//setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

	QVector<int> vect = { 5, 5, 5, 5, 5, 5, 5,5, 5, 5, 5,5, 7, 20, 20, 11, 11, 11, 12 };

	pLayout->setColumnMinimumWidth(0, 600);
	pLayout->setRowMinimumHeight(0, 600);
	pLayout->setRowMinimumHeight(1, 600);
	pLayout->setRowMinimumHeight(2, 600);
	pLayout->setRowMinimumHeight(3, 600);

	pLayout->addWidget(new CHistogram(vect));

	pLayout->addWidget(new CHistogram(vect));

	pLayout->addWidget(new CHistogram(vect));
	
	pLayout->addWidget(new CHistogram(vect));
	
	pLayout->addWidget(new CHistogram(vect));
}

HistogramPaneWidget::~HistogramPaneWidget()
{
}

#include "HistogramPaneWidget.h"
#include <QHeaderView>
#include "HistogramDelegate.h"

HistogramPaneWidget::HistogramPaneWidget(QWidget *parent)
	: QTableView(parent)
{
	m_pModel = new HistogramModel();
	setModel(m_pModel);

	HistogramDelegate *pDelegate = new HistogramDelegate();

	setItemDelegate(pDelegate);
	
	resizeColumnsToContents();
	resizeRowsToContents();

	verticalHeader()->hide();
	horizontalHeader()->hide();
}

HistogramPaneWidget::~HistogramPaneWidget()
{
}

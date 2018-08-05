#include "SpreadSheetPaneWidget.h"
#include <QHeaderView>

SpreadSheetPaneWidget::SpreadSheetPaneWidget(QWidget *parent)
	: QTableView(parent)
{
	m_pModel = new SpreadSheetModel();
	setModel(m_pModel);

	verticalHeader()->hide();
	horizontalHeader()->setStyleSheet("QHeaderView::section { background-color: #BDC3C7; padding: 10px; }");
}

SpreadSheetPaneWidget::~SpreadSheetPaneWidget()
{
}

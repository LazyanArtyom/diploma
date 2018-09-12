#include "MainWorkspaceWidget.h"
#include <QListView>
#include <QTreeView>
#include <QTextEdit>
#include "Histogram.h"

MainWorkspaceWidget::MainWorkspaceWidget(QWidget *parent)
	: QSplitter(parent)
{
	setupUi();
}

MainWorkspaceWidget::~MainWorkspaceWidget()
{
}

void MainWorkspaceWidget::setupUi()
{
	QListView *listview = new QListView;

	m_pSpreadsheetPaneWidget = new SpreadSheetPaneWidget();
	m_pColSelectorWidget = new ColSelectorWidget();
	m_pHistogramPaneWidget = new HistogramPaneWidget();
	
	addWidget(m_pColSelectorWidget);
	addWidget(m_pSpreadsheetPaneWidget);
	addWidget(m_pHistogramPaneWidget);

	setStretchFactor(0, 1);
	setStretchFactor(1, 3);
	setStretchFactor(2, 3);
}

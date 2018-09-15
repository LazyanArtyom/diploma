#include "MainWorkspaceWidget.h"
#include <QListView>
#include <QTreeView>
#include <QTextEdit>
#include "Histogram.h"
#include <QScrollArea>

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

	QScrollArea *pScrollArea = new QScrollArea();
	pScrollArea->setWidget(m_pHistogramPaneWidget);
	pScrollArea->setWidgetResizable(true);

	pScrollArea->setUpdatesEnabled(true);

	addWidget(m_pColSelectorWidget);
	addWidget(m_pSpreadsheetPaneWidget);
	addWidget(pScrollArea);

	setStretchFactor(0, 1);
	setStretchFactor(1, 3);
	setStretchFactor(2, 3);
}

#include "MainWorkspaceWidget.h"
#include <QListView>
#include <QTreeView>
#include <QTextEdit>

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

	QTextEdit *textedit = new QTextEdit;
	
	addWidget(m_pColSelectorWidget);
	addWidget(m_pSpreadsheetPaneWidget);
	addWidget(textedit);

	setStretchFactor(0, 1);
	setStretchFactor(1, 5);
	setStretchFactor(2, 3);
}

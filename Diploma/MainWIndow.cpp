#include "MainWIndow.h"
#include <QToolBar>
#include <QIcon>

MainWIndow::MainWIndow(QWidget *parent)
	: QMainWindow(parent)
{
	m_pMainWorkspace = new MainWorkspaceWidget();
	setCentralWidget(m_pMainWorkspace);
	
	setMinimumSize(1024, 768);
	setWindowIcon(QIcon(":/Resources/icons/histogram.png"));
	setWindowTitle("Histogram");
	showMaximized();

	m_pToolBar = new QToolBar(tr("Toolbar"));
	m_pToolBar->setFixedHeight(100);
	m_pToolBar->setIconSize(QSize(50, 50));
	addToolBar(m_pToolBar);

	const QIcon iconOpen = QIcon(":/Resources/icons/open.png");
	m_pOpenAct = new QAction(iconOpen, tr("Open"), this);
	m_pToolBar->addAction(m_pOpenAct);
	
	m_pToolBar->addSeparator();

	const QIcon iconRun = QIcon(":/Resources/icons/run.png");
	m_pRunAct = new QAction(iconRun, tr("Run"), this);
	m_pToolBar->addAction(m_pRunAct);
}

MainWIndow::~MainWIndow()
{
}

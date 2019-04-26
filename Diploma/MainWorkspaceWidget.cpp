//#include "MainWorkspaceWidget.h"
//#include "HistogramPaneWidget.h"
//#include "HistogramReviewPaneWidget.h"
//
//#include <QScrollArea>
//#include <QElapsedTimer>
//#include <QDebug>
//
//CMainWorkspaceWidget::CMainWorkspaceWidget(QWidget *parent) : QSplitter(parent)
//{
//	setupUi();
//}
//
//CMainWorkspaceWidget::~CMainWorkspaceWidget()
//{
//	if (m_pHistogramContorller != nullptr)
//		delete m_pHistogramContorller;
//}
//
//void CMainWorkspaceWidget::setBinCount(int nBinCount)
//{
//	m_nBinCount = nBinCount;
//}
//
//void CMainWorkspaceWidget::init()
//{
//	QVector<double> data;
//
//	for (int i = 0; i < 100; i++)
//		data << qrand() % 100;
//
//	m_pHistogramContorller->init(data);
//}
//
//void CMainWorkspaceWidget::setupUi()
//{
//	m_pColSelectorWidget = new ColSelectorWidget();
//	m_pHistogramContorller = new CHistogramController();
//
//	CHistogramPaneWidget *pHistogramPaneWidget = m_pHistogramContorller->getHistogramPane();
//	CHistogramReviewPaneWidget *pHistogramReviewPaneWidget = m_pHistogramContorller->getHistogramReviewPane();
//	QObject::connect(pHistogramPaneWidget, SIGNAL(sigHistogramChecked(t_sHistogramData&)),
//		pHistogramReviewPaneWidget, SLOT(onHistogramChecked(t_sHistogramData&)));
//
//	QScrollArea *pScrollArea = new QScrollArea();
//	pScrollArea->setWidgetResizable(true);
//	pScrollArea->setWidget(pHistogramPaneWidget);
//	pScrollArea->setMinimumWidth(900);
//
//	addWidget(m_pColSelectorWidget);
//	addWidget(pScrollArea);
//	addWidget(pHistogramReviewPaneWidget);
//
//	setStretchFactor(0, 1);
//	setStretchFactor(1, 8);
//	setStretchFactor(2, 2);
//}
//
//void CMainWorkspaceWidget::onRun()
//{
//	QElapsedTimer oTimer;
//	oTimer.start();
//		
//	m_pHistogramContorller->run(m_nBinCount);
//		
//	int nCalculationTime = (int)oTimer.elapsed();
//	emit sigCalculationFinished(nCalculationTime);
//}

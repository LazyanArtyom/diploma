#include "MainWorkspaceWidget.h"
#include "HistogramPaneWidget.h"
#include "HistogramReviewPaneWidget.h"

#include <QScrollArea>

MainWorkspaceWidget::MainWorkspaceWidget(QWidget *parent)
	: m_pColSelectorWidget(nullptr),
	  m_pHistogramContorller(nullptr),
	  QSplitter(parent)
{
	setupUi();
}

MainWorkspaceWidget::~MainWorkspaceWidget()
{
	if (m_pHistogramContorller != nullptr)
		delete m_pHistogramContorller;
}

void MainWorkspaceWidget::setupUi()
{
	m_pColSelectorWidget = new ColSelectorWidget();
	m_pHistogramContorller = new CHistogramController();
	m_pHistogramContorller->init(QVector<int>{5, 5, 5, 5, 10, 10, 10});

	CHistogramPaneWidget *pHistogramPaneWidget = m_pHistogramContorller->getHistogramPane();
	CHistogramReviewPaneWidget *pHistogramReviewPaneWidget = m_pHistogramContorller->getHistogramReviewPane();
	QObject::connect(pHistogramPaneWidget, SIGNAL(sigHistogramChecked(t_sHistogramData&)), pHistogramReviewPaneWidget, SLOT(onHistogramChecked(t_sHistogramData&)));

	QScrollArea *pScrollArea = new QScrollArea();
	pScrollArea->setWidgetResizable(true);
	pScrollArea->setWidget(pHistogramPaneWidget);

	addWidget(m_pColSelectorWidget);
	addWidget(pScrollArea);
	addWidget(pHistogramReviewPaneWidget);

	setStretchFactor(0, 1);
	setStretchFactor(1, 4);
	setStretchFactor(2, 3);
}

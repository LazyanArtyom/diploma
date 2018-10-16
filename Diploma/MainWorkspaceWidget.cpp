#include "MainWorkspaceWidget.h"
#include "Histogram.h"
#include <QScrollArea>

MainWorkspaceWidget::MainWorkspaceWidget(QWidget *parent)
	: m_pColSelectorWidget(nullptr),
	  m_pHistogramReviewPaneWidget(nullptr),
	  m_pHistogramPainter(nullptr), 
	  m_pHistogramPaneWidget(nullptr), 
	  QSplitter(parent)
{
	setupUi();
}

MainWorkspaceWidget::~MainWorkspaceWidget()
{
	delete m_pHistogramPainter;
}

void MainWorkspaceWidget::setupUi()
{
	QListView *listview = new QListView;

	m_pHistogramReviewPaneWidget = new CHistogramReviewPaneWidget();
	
	m_pColSelectorWidget = new ColSelectorWidget();
	QStringList cols { "Bin", "Details", "DieX", "DieY" };
	m_pColSelectorWidget->AddColumns(cols);

	m_pHistogramPaneWidget = new CHistogramPaneWidget();
	m_pHistogramPainter = new CHistogramPainter();

	m_pHistogramReviewPaneWidget->setPainter(m_pHistogramPainter);
	m_pHistogramPaneWidget->setPainter(m_pHistogramPainter);

	m_pHistogramPaneWidget->init();

	QScrollArea *pScrollArea = new QScrollArea();
	pScrollArea->setWidgetResizable(true);
	pScrollArea->setWidget(m_pHistogramPaneWidget);

	addWidget(m_pColSelectorWidget);
	addWidget(pScrollArea);
	addWidget(m_pHistogramReviewPaneWidget);

	setStretchFactor(0, 1);
	setStretchFactor(1, 4);
	setStretchFactor(2, 3);

	QObject::connect(m_pHistogramPaneWidget, SIGNAL(sigHistogramChecked(t_sHistogramConfig&)), m_pHistogramReviewPaneWidget, SLOT(onHistogramChecked(t_sHistogramConfig&)));
}

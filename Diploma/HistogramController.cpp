#include "HistogramController.h"

CHistogramController::CHistogramController() 
	: m_pHistogramModel(nullptr),
	m_pHistogramPainter(nullptr),
	m_pHistogramPaneWidget(nullptr),
	m_pHistogramReviewPaneWidget(nullptr)
{
	m_pHistogramModel = new CHistogramModel();

	m_pHistogramPainter = new CHistogramPainter();
	m_pHistogramPaneWidget = new CHistogramPaneWidget();
	m_pHistogramReviewPaneWidget = new CHistogramReviewPaneWidget();

	m_pHistogramPaneWidget->setPainter(m_pHistogramPainter);
	m_pHistogramReviewPaneWidget->setPainter(m_pHistogramPainter);
}

CHistogramController::~CHistogramController()
{
	if (m_pHistogramModel != nullptr)
		delete m_pHistogramModel;
	if (m_pHistogramPaneWidget != nullptr)
		delete m_pHistogramPaneWidget;
	if (m_pHistogramReviewPaneWidget != nullptr)
		delete m_pHistogramReviewPaneWidget;
	if (m_pHistogramPainter != nullptr)
		delete m_pHistogramPainter;
}

void CHistogramController::init(QVector<int> aData)
{
	m_pHistogramModel->setData(aData);
	t_sHistogramData oHistogramData = m_pHistogramModel->run();
	m_pHistogramPaneWidget->addHistogram(oHistogramData);
	m_pHistogramPaneWidget->addHistogram(oHistogramData);
	m_pHistogramPaneWidget->addHistogram(oHistogramData);
}

CHistogramPaneWidget *CHistogramController::getHistogramPane()
{
	return m_pHistogramPaneWidget;
}

CHistogramReviewPaneWidget *CHistogramController::getHistogramReviewPane()
{
	return m_pHistogramReviewPaneWidget;
}

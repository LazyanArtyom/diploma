#include "HistogramReviewPaneWidget.h"
#include "Histogram.h"
#include <QVBoxLayout>
#include <QDesktopWidget>
#include <QPushButton>
#include <QIcon>
#include <QSize>

CHistogramReviewPaneWidget::CHistogramReviewPaneWidget(QWidget *pParent)
	: m_pHistogramPainter(nullptr), m_bIsChecked(false), QWidget(pParent)
{
	setMinimumWidth(500);
}

CHistogramReviewPaneWidget::~CHistogramReviewPaneWidget() {}

void CHistogramReviewPaneWidget::setConfig(const t_sHistogramConfig &oCfg)
{
	m_oCfg = oCfg;
}

void CHistogramReviewPaneWidget::setPainter(CHistogramPainter *pHistogramPainter)
{
	m_pHistogramPainter = pHistogramPainter;
}

void CHistogramReviewPaneWidget::updateConfig()
{
	m_oCfg.nHeight = this->height();
	m_oCfg.nWidth = this->width();

	m_oCfg.nWidth -= m_oCfg.nLeftMargin;
	m_oCfg.nHeight -= m_oCfg.nBottomMargin;
}

void CHistogramReviewPaneWidget::paintEvent(QPaintEvent *pEvent)
{
	if (m_bIsChecked)
	{
		updateConfig();
		QPainter painter(this);
		m_pHistogramPainter->draw(&painter, m_oCfg);
	}
}

void CHistogramReviewPaneWidget::onHistogramChecked(t_sHistogramConfig &oCfg)
{
	setConfig(oCfg);
	m_bIsChecked = true;
	update();
}
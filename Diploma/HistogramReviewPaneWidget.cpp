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

void CHistogramReviewPaneWidget::setHistogramData(const t_sHistogramData &oHistogramData)
{
	m_oHistogramData = oHistogramData;
}

void CHistogramReviewPaneWidget::setPainter(CHistogramPainter *pHistogramPainter)
{
	m_pHistogramPainter = pHistogramPainter;
}

void CHistogramReviewPaneWidget::paintEvent(QPaintEvent *pEvent)
{
	QPainter painter(this);
	
	if (m_bIsChecked)
	{
		m_pHistogramPainter->draw(&painter, m_oHistogramData, geometry());
	}
	else
	{
		painter.setPen(QPen(Qt::darkGray, Qt::SolidLine));
		painter.setFont(QFont("Arial", width() / 20, QFont::Normal));
		painter.fillRect(0, 0, width(), height(), Qt::gray);
		painter.drawText(0, 0, width(), height() / 6, Qt::AlignCenter, "Histogram Review");
	}
}

void CHistogramReviewPaneWidget::onHistogramChecked(t_sHistogramData &oHistogramData)
{
	m_bIsChecked = true;
	m_oHistogramData = oHistogramData;
	update();
}
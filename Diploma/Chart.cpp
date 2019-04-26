#include <QPainter>

// Local includes
#include "Chart.h"
#include "ChartPainter.h"

////////////////////////////////////////////////////////////////////////////////
//
//	CHistogram
//
CHistogram::CHistogram(CHistogramData* pHistogramData, CHistogramPainter* pHistogramPainter, QWidget *pParent)
	: m_pHistogramData(pHistogramData), m_pHistogramPainter(pHistogramPainter), IChart(pParent)
{
	installEventFilter(pParent);
	setMinimumSize(400, 300);
}

CHistogram::~CHistogram()
{
}

void CHistogram::paintEvent(QPaintEvent *pEvent)
{
	Q_UNUSED(pEvent);

	QPainter painter(this);

	m_pHistogramPainter->draw(&painter, m_pHistogramData, geometry());
}
////////////////////////////////////////////////////////////////////////////////
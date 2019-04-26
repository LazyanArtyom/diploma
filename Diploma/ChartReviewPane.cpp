// Local includes
#include "ChartPainter.h"
#include "ChartReviewPane.h"

////////////////////////////////////////////////////////////////////////////////
//
//	ChartReviewPane
//
ChartReviewPane::ChartReviewPane(QWidget *pParent) : QWidget(pParent)
{
	setMinimumWidth(500);
}

void ChartReviewPane::paintEvent(QPaintEvent *pEvent)
{
	QPainter painter(this);
	
	if (m_bIsChecked && (m_pChartData != nullptr))
		m_pPainter->draw(&painter, m_pChartData, geometry());
	else
	{
		painter.setPen(QPen(Qt::darkGray, Qt::SolidLine));
		painter.setFont(QFont("Arial", width() / 20, QFont::Normal));
		painter.fillRect(0, 0, width(), height(), Qt::gray);
		painter.drawText(0, 0, width(), height() / 6, Qt::AlignCenter, "Histogram Review");
	}
}

void ChartReviewPane::onChartChecked(IChartData* pChartData, IPainter* pPainter)
{
	if (pChartData == nullptr || pPainter == nullptr)
		return;

	m_bIsChecked = true;
	m_pPainter = pPainter;
	m_pChartData = pChartData;

	update();
}
////////////////////////////////////////////////////////////////////////////////
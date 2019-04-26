#include <QtMath>

// Local includes
#include "ChartPainter.h"

////////////////////////////////////////////////////////////////////////////////
//
//	CHistogramPainter
//
CHistogramPainter::CHistogramPainter() 
	: m_nHeaderHeight(0), m_nFooterHeight(0)
{
}

void CHistogramPainter::draw(QPainter *pPainter, IChartData* pChartData, QRect rect)
{
	CHistogramData* pHistogramData = dynamic_cast<CHistogramData*>(pChartData);
	if (pHistogramData == nullptr)
		return;

	m_oHistogramData = pHistogramData;

	QFont font("Arial", 14, QFont::Normal);
	QFontMetrics fMetrics(font);
	
	//nMaxFrequencyCount
	m_nLeftMargin = fMetrics.width(QString::number(pHistogramData->aFrequencyTable.count())) + 25;
	m_nRightMargin = fMetrics.width(QString::number(pHistogramData->nMaxValue)) / 2 + 10;
	m_nTopMargin = fMetrics.height();
	m_nBottomMargin = fMetrics.height() * 2;

	pPainter->save();

	pPainter->setPen(QPen(Qt::darkGray, 1, Qt::SolidLine));
	m_oRect.setSize(QSize(rect.width() - 1, rect.height() - 1));
	
	pPainter->drawRect(m_oRect);
	pPainter->restore();

	drawHeader(pPainter);
}

void CHistogramPainter::drawHeader(QPainter *pPainter)
{
	m_nHeaderHeight = m_oRect.height() / 10;
	int nHeaderWidth = m_oRect.width();

	pPainter->save();

	QRect rect(0, 0, nHeaderWidth, m_nHeaderHeight);

	QFont font("Arial", m_nHeaderHeight / 3, QFont::Normal);
	pPainter->setPen(QPen(Qt::darkGray, 1, Qt::SolidLine));
	pPainter->drawLine(0, m_nHeaderHeight, nHeaderWidth, m_nHeaderHeight);
	pPainter->setFont(font);
	pPainter->drawText(rect, Qt::AlignCenter, m_oHistogramData->sName);

	pPainter->restore();

	drawPlot(pPainter);
}

void CHistogramPainter::drawFooter(QPainter *pPainter)
{
	// change cordinates to bottom left
	pPainter->translate(0, m_oRect.height());

	m_nFooterHeight = m_oRect.height() / 5;
	int nFooterWidth = m_oRect.width();

	pPainter->save();

	QRect rect(0, 0, nFooterWidth, -m_nFooterHeight);

	QFont font("Arial", m_nFooterHeight / 20, QFont::Normal);
	pPainter->setPen(QPen(Qt::darkGray, 3, Qt::SolidLine));
	pPainter->setFont(font);
	pPainter->setPen(QPen(Qt::darkGray, 3, Qt::SolidLine));

	pPainter->drawText(rect, Qt::AlignCenter, "N_ColName");

	pPainter->restore();

	pPainter->translate(0, -m_nFooterHeight);

	drawPlot(pPainter);
}

void CHistogramPainter::drawPlot(QPainter *pPainter)
{
	drawAxes(pPainter);
}

void CHistogramPainter::drawAxes(QPainter *pPainter)
{
	QFont font("Arial", (m_oRect.width() + m_oRect.height()) / 70);
	QFontMetrics fMetrics(font);

	fMetrics.width(QString::number(0));
	int nBottomMargin = fMetrics.height() + 10;
	// change cordinates to bottom left
	pPainter->translate(0, m_oRect.height() - nBottomMargin);

	// calculate Left margin size
	int nMaxNumber = 0;
	for (int i = 0; i < m_oHistogramData->aFrequencyTable.count(); ++i)
	{
		if (m_oHistogramData->aFrequencyTable[i] > nMaxNumber)
			nMaxNumber = m_oHistogramData->aFrequencyTable[i];
	}
	int nLeftMargin = fMetrics.width(QString::number(nMaxNumber)) + nBottomMargin;

	pPainter->translate(nLeftMargin, 0);

	pPainter->save();

	pPainter->setPen(QPen(Qt::black, 2, Qt::SolidLine));
	pPainter->setFont(font);

	// Y axis
	int nYSize = m_oRect.height() - (m_nHeaderHeight + nBottomMargin + 10);
	int nYOffset = nYSize / 9;
	int nYCordinateOffset = qCeil(nMaxNumber / 9.0);
	
	pPainter->drawLine(QLine(0, 0, 0, -nYSize));
	
	for (int nY = 0, nYCordinate = 0; nY <= nYSize; nY += nYOffset, nYCordinate += nYCordinateOffset)
	{
		int nTextWidth = fMetrics.width(QString::number(nYCordinate));
		int nTextHeight = fMetrics.height();

		// draw Y cordinates
		pPainter->drawLine(QLine(-5, -nY, 5, -nY));
		pPainter->drawText(-10, -(nY + int(nTextHeight / 2)), -(nTextWidth + 10), nTextHeight, Qt::AlignCenter, QString::number(nYCordinate));
	}
	
	// X axis
	int nTextWidth = fMetrics.width(QString::number(m_oHistogramData->nMaxValue));
	int nXSize = m_oRect.width() - nLeftMargin - nTextWidth;
	pPainter->drawLine(QLine(0, 0, nXSize, 0));
	
	int nXOffset = qCeil(nXSize / m_oHistogramData->nBinsCount);
	int nXCordinatesOffset = m_oHistogramData->nBinsRange;

	int nIndex = 0;
	double nBinScale = double(nYSize / 9) / nYCordinateOffset;
	for (int nX = 0, nXCordinate = m_oHistogramData->nMinValue; nX <= nXSize; nX += nXOffset, nXCordinate += nXCordinatesOffset)
	{
		int nTextWidth = fMetrics.width(QString::number(nXCordinate));
		int nTextHeight = fMetrics.height();

		if ((nX + nXOffset) <= nXSize)
		{
			drawBin(pPainter, nIndex, QPair<int, int>(nX, nXOffset - 1), nBinScale);
			nIndex++;
		}

		// draw X cordinates
		pPainter->drawLine(QLine(nX, 5, nX, -5));
		pPainter->drawText(nX - int(nTextWidth / 2), 3, nTextWidth, nTextHeight + 10, Qt::AlignCenter, QString::number(nXCordinate));
	}
	
	pPainter->restore();
}

void CHistogramPainter::drawBin(QPainter *pPainter, int nBinIndex, QPair<int, int> range, double nScale)
{
	pPainter->save();

	pPainter->setPen(QPen(Qt::black, 1, Qt::SolidLine));
	pPainter->setOpacity(0.6);
	pPainter->setBrush(Qt::blue);

	if (nBinIndex >= m_oHistogramData->aFrequencyTable.count())
		nBinIndex = m_oHistogramData->aFrequencyTable.count() - 1;

	int nHeight = -(m_oHistogramData->aFrequencyTable[nBinIndex] * nScale);

	pPainter->drawRect(range.first, 0, range.second, nHeight);

	pPainter->restore();
}
////////////////////////////////////////////////////////////////////////////////
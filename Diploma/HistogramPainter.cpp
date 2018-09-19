#include "HistogramPainter.h"
#include <QtMath>

CHistogramPainter::CHistogramPainter()
{
}


CHistogramPainter::~CHistogramPainter()
{
}

void CHistogramPainter::draw(QPainter *pPainter, t_sHistogramConfig &oCfg)
{
	clear();
	m_oCfg = oCfg;

	pPainter->save();

	// top margin
	pPainter->translate(0, 3);

	pPainter->setPen(QPen(Qt::darkGray, 1, Qt::SolidLine));
	pPainter->drawRect(QRect
	(0, 0, m_oCfg.nWidth + m_oCfg.nLeftMargin - 1, m_oCfg.nHeight + m_oCfg.nTopMargin + 18));

	pPainter->restore();

	drawHeader(pPainter);
}

void CHistogramPainter::drawPlot(QPainter *pPainter)
{
	pPainter->translate(m_oCfg.nLeftMargin, 0);
	drawAxes(pPainter);
	drawBins(pPainter);
}

void CHistogramPainter::drawAxes(QPainter *pPainter)
{
	pPainter->save();

	QFont font("Arial", 14, QFont::Normal);
	pPainter->setPen(QPen(Qt::black, 2, Qt::SolidLine));
	pPainter->setFont(font);
	QFontMetrics fMetrics(font);

	m_oCfg.nHeight -= m_oCfg.nTopMargin;
	m_oCfg.nWidth -= m_oCfg.nRightMargin;

	int nYOffset = m_oCfg.nHeight / 9;

	// Y axis
	pPainter->drawLine(QLine(0, 0, 0, -m_oCfg.nHeight));

	for (int nY = 0, nYCordinate = 0; nY <= m_oCfg.nHeight; nY += nYOffset, nYCordinate += m_oCfg.nYCordinatesOffset)
	{
		int nTextWidth = fMetrics.width(QString::number(nYCordinate));
		int nTextHeight = fMetrics.height();

		// draw Y cordinates
		pPainter->drawLine(QLine(-5, -nY, 5, -nY));
		pPainter->drawText(-10, -(nY + int(nTextHeight / 2)), -(nTextWidth + 10), nTextHeight, Qt::AlignCenter, QString::number(nYCordinate));
	}

	// X axis
	pPainter->drawLine(QLine(0, 0, m_oCfg.nWidth, 0));

	int nXOffset = qCeil(m_oCfg.nWidth / m_oCfg.nBinsCount);
	int nXCordinatesOffset = m_oCfg.nBinsWidth;

	for (int nX = 0, nXCordinate = m_oCfg.nMinValue; nX <= m_oCfg.nWidth; nX += nXOffset, nXCordinate += nXCordinatesOffset)
	{
		int nTextWidth = fMetrics.width(QString::number(nXCordinate));
		int nTextHeight = fMetrics.height();

		if ((nX + nXOffset) <= m_oCfg.nWidth)
		{
			CBin *pBin = new CBin(nX, nXOffset - 1);
			pBin->setRange(nXCordinate, (nXCordinate + nXCordinatesOffset) - 1);
			m_lstBins << pBin;
		}

		// draw X cordinates
		pPainter->drawLine(QLine(nX, 5, nX, -5));
		pPainter->drawText(nX - int(nTextWidth / 2), 10, nTextWidth, nTextHeight + 10, Qt::AlignCenter, QString::number(nXCordinate));
	}

	pPainter->restore();
}

void CHistogramPainter::drawBins(QPainter *pPainter)
{
	pPainter->save();

	pPainter->setPen(QPen(Qt::black, 1, Qt::SolidLine));
	pPainter->setOpacity(0.6);
	pPainter->setBrush(Qt::blue);

	for (const auto &value : m_oCfg.mapFrequency.toStdMap())
	{
		for (const auto &pBin : m_lstBins)
		{
			CRange *pRange = pBin->getRange();
			if (pRange->inRange(value.first))
			{
				pBin->increaseHeight(value.second);
				break;
			}
		}
	}

	for (const auto &pBin : m_lstBins)
	{
		CRange *pRange = pBin->getRange();
		int nHeight = pBin->getHeight();
		QPair<int, int> nWidth = pBin->getWidth();
		int height = -((nHeight * qCeil(m_oCfg.nHeight / 9)) / m_oCfg.nYCordinatesOffset);

		pPainter->drawRect(nWidth.first, 0, nWidth.second, height);

	}

	pPainter->restore();
}

void CHistogramPainter::drawHeader(QPainter *pPainter)
{
	int nHeaderHeight = m_oCfg.nHeight / 10;

	pPainter->save();

	QRect rect(0, 0, m_oCfg.nWidth + m_oCfg.nLeftMargin, nHeaderHeight);

	QFont font("Arial", nHeaderHeight / 2, QFont::Normal);
	pPainter->setPen(QPen(Qt::darkGray, 1, Qt::SolidLine));
	pPainter->drawLine(0, nHeaderHeight, m_oCfg.nWidth + m_oCfg.nLeftMargin, nHeaderHeight);
	pPainter->setFont(font);
	pPainter->drawText(rect, Qt::AlignCenter, "Histogram");

	pPainter->restore();

	// change cordinates to bottom left
	pPainter->translate(0, m_oCfg.nHeight + m_oCfg.nTopMargin + 10);

	m_oCfg.nHeight -= nHeaderHeight;

	drawFooter(pPainter);
}

void CHistogramPainter::drawFooter(QPainter *pPainter)
{
	int nFooterHeight = m_oCfg.nHeight / 15;

	pPainter->save();

	QRect rect(0, 0, m_oCfg.nWidth + m_oCfg.nLeftMargin, -nFooterHeight);

	QFont font("Arial", nFooterHeight / 2, QFont::Normal);
	pPainter->setPen(QPen(Qt::darkGray, 3, Qt::SolidLine));
	//pPainter->drawRect(rect);
	pPainter->setFont(font);
	pPainter->setPen(QPen(Qt::darkGray, 3, Qt::SolidLine));
	pPainter->drawText(rect, Qt::AlignCenter, "N_ColName");

	pPainter->restore();

	pPainter->translate(0, -(nFooterHeight + m_oCfg.nBottomMargin));

	m_oCfg.nHeight -= nFooterHeight;

	drawPlot(pPainter);
}

void CHistogramPainter::clear()
{
	if (!m_lstBins.isEmpty())
	{
		for (auto &pBin : m_lstBins)
			if (pBin != nullptr)
				delete pBin;

		m_lstBins.clear();
	}
}

CBin::CBin(int nX1, int nX2) : m_nBinHeight(0), m_pRange(nullptr)
{
	m_nBinWidth = QPair<int, int>(nX1, nX2);
}

CBin::~CBin()
{
	if (m_pRange != nullptr)
		delete m_pRange;
}


int CBin::getHeight()
{
	return m_nBinHeight;
}

QPair<int, int> CBin::getWidth()
{
	return m_nBinWidth;
}

void CBin::increaseHeight(int nVal)
{
	m_nBinHeight += nVal;
}

void CBin::setRange(int nLow, int nHigh)
{
	m_pRange = new CRange(nLow, nHigh);
}

CRange* CBin::getRange()
{
	return m_pRange;
}

CRange::CRange(int nLow, int nHigh) : m_nLow(nLow), m_nHigh(nHigh) {}

bool CRange::inRange(int nValue)
{
	return (unsigned(nValue - m_nLow) <= m_nHigh - m_nLow);
}

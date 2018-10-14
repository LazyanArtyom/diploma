#include "HistogramPainter.h"
#include <QtMath>

CHistogramPainter::CHistogramPainter() : m_sTitle(""), m_nHeaderHeight(0), m_nFooterHeight(0)
{
}


CHistogramPainter::~CHistogramPainter()
{
}

void CHistogramPainter::draw(QPainter *pPainter, t_sHistogramData &oHistogramData, QRect rect)
{
//	clear();
//	m_oCfg = oCfg;
	m_oHistogramData = oHistogramData;

	QFont font("Arial", 14, QFont::Normal);
	QFontMetrics fMetrics(font);

	m_nLeftMargin = fMetrics.width(QString::number(m_oCfg.nMaxFrequencyCount)) + 25;
	m_nRightMargin = fMetrics.width(QString::number(m_oCfg.nMaxValue)) / 2 + 10;
	m_nTopMargin = fMetrics.height();
	m_nBottomMargin = fMetrics.height() * 2;

	//m_oHistogramData.nWidth -= m_nLeftMargin;
	//m_oHistogramData.nHeight -= m_nBottomMargin;

	pPainter->save();

	// top margin
	//pPainter->translate(0, 3);

	pPainter->setPen(QPen(Qt::darkGray, 1, Qt::SolidLine));
	//pPainter->drawRect(QRect
	//(0, 0, m_oCfg.nWidth + m_oCfg.nLeftMargin - 1, m_oCfg.nHeight + m_oCfg.nTopMargin + 18));
	
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

	QFont font("Arial", m_nHeaderHeight / 2, QFont::Normal);
	pPainter->setPen(QPen(Qt::darkGray, 1, Qt::SolidLine));
	pPainter->drawLine(0, m_nHeaderHeight, nHeaderWidth, m_nHeaderHeight);
	pPainter->setFont(font);
	pPainter->drawText(rect, Qt::AlignCenter, m_sTitle);

	pPainter->restore();

	//m_oCfg.nHeight -= nHeaderHeight;

	drawFooter(pPainter);
}

void CHistogramPainter::drawFooter(QPainter *pPainter)
{
	// change cordinates to bottom left
	pPainter->translate(0, m_oRect.height());

	m_nFooterHeight = m_oRect.height() / 15;
	int nFooterWidth = m_oRect.width();

	pPainter->save();

	QRect rect(0, 0, nFooterWidth, -m_nFooterHeight);

	QFont font("Arial", m_nFooterHeight / 2, QFont::Normal);
	pPainter->setPen(QPen(Qt::darkGray, 3, Qt::SolidLine));
	pPainter->setFont(font);
	pPainter->setPen(QPen(Qt::darkGray, 3, Qt::SolidLine));

	pPainter->drawText(rect, Qt::AlignCenter, "N_ColName");

	pPainter->restore();

	pPainter->translate(0, -m_nFooterHeight);

	//m_oCfg.nHeight -= nFooterHeight;

	drawPlot(pPainter);
}

void CHistogramPainter::drawPlot(QPainter *pPainter)
{
	//pPainter->translate(m_oCfg.nLeftMargin, 0);
	drawAxes(pPainter);
	//drawBins(pPainter);
}

void CHistogramPainter::drawAxes(QPainter *pPainter)
{
	QFont font("Arial", 14, QFont::Normal);
	QFontMetrics fMetrics(font);

	// calculate Left margin size
	int nMaxNumber = 0;
	for (int i = 0; i < m_oHistogramData.aFrequencyTable.count(); ++i)
	{
		if (m_oHistogramData.aFrequencyTable[i] > nMaxNumber)
			nMaxNumber = m_oHistogramData.aFrequencyTable[i];
	}
	int nLeftMargin = fMetrics.width(nMaxNumber) + 25;

	pPainter->translate(nLeftMargin, 0);

	pPainter->save();

	pPainter->setPen(QPen(Qt::black, 2, Qt::SolidLine));
	pPainter->setFont(font);

	//m_oCfg.nHeight -= m_oCfg.nTopMargin;
	//m_oCfg.nWidth -= m_oCfg.nRightMargin;

	// Y axis
	int nYSize = m_oRect.height() - (m_nHeaderHeight + m_nFooterHeight + 10);
	int nYOffset = nYSize / 9;
	
	pPainter->drawLine(QLine(0, 0, 0, -nYSize));
	/*
	for (int = 0, nYCordinate = 0; nY <= m_oCfg.nHeight; nY += nYOffset, nYCordinate += m_oCfg.nYCordinatesOffset)
	{
		int nTextWidth = fMetrics.width(QString::number(nYCordinate));
		int nTextHeight = fMetrics.height();

		// draw Y cordinates
		pPainter->drawLine(QLine(-5, -nY, 5, -nY));
		pPainter->drawText(-10, -(nY + int(nTextHeight / 2)), -(nTextWidth + 10), nTextHeight, Qt::AlignCenter, QString::number(nYCordinate));
	}
	*/
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
	*/
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

void CHistogramPainter::setTitle(const QString sTitle)
{
	m_sTitle = sTitle;
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

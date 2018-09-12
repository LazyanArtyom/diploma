#include "Histogram.h"
#include <QDebug>
#include <QPainter>
#include <QtMath>
#include <QFontMetrics>

CHistogram::CHistogram(QVector<int> vectData, QWidget *pParent) : QWidget(pParent)
{
	m_vectData = vectData;
	m_nBinsCount = 0;
	m_nHeight = 0;
	m_nWidht = 0;
	m_nMaxFrequencyCount = 0;
	m_nBinsWidth = 0;
	m_nMin = 0;
	m_nMax = 0;

	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	setMinimumWidth(300);
	setMinimumHeight(300);

	run();
	update();
}

CHistogram::~CHistogram()
{
	clear();
}

void CHistogram::resizeEvent(QResizeEvent *pEvent)
{
	Q_UNUSED(pEvent);

	m_nHeight = pEvent->size().height();
	m_nWidht = pEvent->size().width();

	//m_nHeight -= 100;
	//m_nWidht -= 100;

	update();
}

void CHistogram::paintEvent(QPaintEvent *pEvent)
{
	Q_UNUSED(pEvent);

	clear();

	QPainter painter(this);

	QFont font("Arial", 14, QFont::Normal);
	painter.setPen(QPen(Qt::black, 3, Qt::SolidLine));
	painter.setFont(font);
	QFontMetrics fMetrics(font);

	int lOffset = fMetrics.width(QString::number(m_nMaxFrequencyCount));
	int rOffset = fMetrics.width(QString::number(m_nMax));

	painter.translate(lOffset + 20, m_nHeight - 45);
	m_nWidht -= (lOffset + 30);
	m_nHeight -= 150;

	//drawHeader(&painter);
	drawPlot(&painter);
	//drawFooter(&painter);
}

void CHistogram::drawPlot(QPainter *pPainter)
{
	drawAxes(pPainter);
	drawBins(pPainter);
}

void CHistogram::drawAxes(QPainter *pPainter)
{
	pPainter->save();

	QFont font("Arial", 14, QFont::Normal);
	pPainter->setPen(QPen(Qt::black, 3, Qt::SolidLine));
	pPainter->setFont(font);
	QFontMetrics fMetrics(font);

	int nYOffset = m_nHeight / 9;
	int nYCordinatesOffset = m_nMaxFrequencyCount / 9;

	// Y axis
	pPainter->drawLine(QLine(0, 0, 0, -(m_nHeight + nYOffset)));

	for (int i = 0, nYCordinate = 0; nYCordinate <= m_nMaxFrequencyCount; i += nYOffset, nYCordinate += nYCordinatesOffset)
	{
		int nTextWidth = fMetrics.width(QString::number(nYCordinate));
		int nTextHeight = fMetrics.height();

		// draw Y cordinates
		pPainter->drawLine(QLine(-5, -i, 5, -i));
		pPainter->drawText(-10, -( i + int(nTextHeight / 2) ), -(nTextWidth + 10), nTextHeight, Qt::AlignCenter, QString::number(nYCordinate));
	}

	// X axis
	pPainter->drawLine(QLine(0, 0, m_nWidht, 0));

	int nXOffset = qCeil(m_nWidht / m_nBinsCount);
	int nXCordinatesOffset = m_nBinsWidth;

	for (int i = 0, nXCordinate = m_nMin; i <= m_nWidht; i += nXOffset, nXCordinate += nXCordinatesOffset)
	{
		int nTextWidth = fMetrics.width(QString::number(nXCordinate));
		int nTextHeight = fMetrics.height();

		if ((i + nXOffset) <= m_nWidht)
		{
			CBin *pBin = new CBin(i, nXOffset);
			pBin->setRange(nXCordinate, (nXCordinate + nXCordinatesOffset) - 1);
			m_lstBins << pBin;
		}

		// draw X cordinates
		pPainter->drawLine(QLine(i, 5, i, -5));
		pPainter->drawText(i - int(nTextWidth / 2), 10, nTextWidth, nTextHeight + 10, Qt::AlignCenter, QString::number(nXCordinate));
	}

	pPainter->restore();
}

void CHistogram::drawBins(QPainter *pPainter)
{
	pPainter->save();

	pPainter->setPen(QPen(Qt::black, 1, Qt::SolidLine));
	pPainter->setBrush(QColor(0, 0, 204));

	for (const auto &value : m_mapFrequency.toStdMap())
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
		int nYCordinatesOffset = qCeil(m_nMaxFrequencyCount / 9);
		int height = -((nHeight * qCeil(m_nHeight / 9)) / nYCordinatesOffset);
	
		pPainter->drawRect(nWidth.first, 0, nWidth.second, height);
		
	}

	pPainter->restore();
}

void CHistogram::drawHeader(QPainter *pPainter)
{
	pPainter->save();
	
	QRect rect(0, 0, m_nWidht, 80);

	QFont font("Arial", 36, QFont::Normal);
	pPainter->setPen(QPen(Qt::darkGray, 3, Qt::SolidLine));
	pPainter->setOpacity(0.1);
	pPainter->drawRect(rect);
	pPainter->setOpacity(1);
	pPainter->setFont(font);
	pPainter->setPen(QPen(Qt::darkGray, 3, Qt::SolidLine));
	pPainter->drawText(rect, Qt::AlignCenter, "CHistogram");

	pPainter->restore();
}

void CHistogram::drawFooter(QPainter *pPainter)
{
	pPainter->save();
	
	QRect rect(0, 0, m_nWidht, -40);

	pPainter->translate(0, m_nHeight);
	QFont font("Arial", 24, QFont::Normal);
	pPainter->setPen(QPen(Qt::darkGray, 3, Qt::SolidLine));
	pPainter->setOpacity(0.1);
	pPainter->drawRect(rect);
	pPainter->setOpacity(1);
	pPainter->setFont(font);
	pPainter->setPen(QPen(Qt::darkGray, 3, Qt::SolidLine));
	pPainter->drawText(rect, Qt::AlignCenter, "CHistogram");

	pPainter->restore();
}

void CHistogram::clear()
{
	for (auto &pBin : m_lstBins)
		delete pBin;

	m_lstBins.clear();
}

void CHistogram::run()
{
	for (int i = 0; i < m_vectData.count(); i++)
	{
		QMap<int, int>::iterator iter = m_mapFrequency.find(m_vectData[i]);
		if (iter != m_mapFrequency.end())
		{
			iter.value()++;
			if (iter.value() > m_nMaxFrequencyCount)
				m_nMaxFrequencyCount = iter.value();
		}
		else
			m_mapFrequency.insert(m_vectData[i], 1);
	}

	m_nBinsCount = qFloor(1 + 3.22 * log(m_vectData.count()));

	if (m_nMaxFrequencyCount < 9)
		m_nMaxFrequencyCount = 9;

	if (m_nBinsCount > 20)
		m_nBinsCount = 20;
	else if (m_nBinsCount < 5)
		m_nBinsCount = 5;

	m_nMin = m_mapFrequency.firstKey();
	m_nMax = m_mapFrequency.lastKey();

	m_nBinsWidth = qCeil((m_nMax - m_nMin) / (double)m_nBinsCount);
}

CHistogram::CBin::CBin(int nX1, int nX2) : m_nBinHeight(0), m_pRange(nullptr)
{
	m_nBinWidth = QPair<int, int>(nX1, nX2);
}

CHistogram::CBin::~CBin()
{
	if (m_pRange != nullptr)
		delete m_pRange;
}

QRect CHistogram::CBin::getRect()
{
	return QRect(m_nBinWidth.first, 0, m_nBinWidth.second, -250);
}

int CHistogram::CBin::getHeight()
{
	return m_nBinHeight;
}

QPair<int, int> CHistogram::CBin::getWidth()
{
	return m_nBinWidth;
}

void CHistogram::CBin::setScale(int nScale)
{
	m_BinScale = nScale;
}

void CHistogram::CBin::increaseHeight(int nVal)
{
	m_nBinHeight += nVal;
}

void CHistogram::CBin::setRange(int nLow, int nHigh)
{
	m_pRange = new CRange(nLow, nHigh);
}

CHistogram::CRange* CHistogram::CBin::getRange()
{
	return m_pRange;
}

CHistogram::CRange::CRange(int nLow, int nHigh) : m_nLow(nLow), m_nHigh(nHigh) {}

bool CHistogram::CRange::inRange(int nValue)
{
	return (unsigned(nValue - m_nLow) <= m_nHigh - m_nLow);
}

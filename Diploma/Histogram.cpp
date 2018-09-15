#include "Histogram.h"
#include <QDebug>
#include <QPainter>
#include <QtMath>
#include <QFontMetrics>
#include <QDebug>
#include <QHBoxLayout>

CPlot::CPlot(QVector<int> vectData, QWidget *pParent) : QWidget(pParent)
{
	m_vectData = vectData;
	m_nBinsCount = 0;
	m_nHeight = 0;
	m_nWidth = 0;
	m_nMaxFrequencyCount = 0;
	m_nBinsWidth = 0;
	m_nMin = 0;
	m_nMax = 0;

	m_nLeftMargin = 0;
	m_nRightMargin = 0;
	m_nTopMargin = 0;
	m_nBottomMargin = 0;

	m_nYCordinatesOffset = 0;
	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

	run();
}

CPlot::~CPlot()
{
	clear();
}

void CPlot::resizeEvent(QResizeEvent *pEvent)
{
	Q_UNUSED(pEvent);

	m_nHeight = this->height();
	m_nWidth = this->width();
	//m_nHeight = pEvent->size().height();
	//m_nWidth = pEvent->size().width();

	QFont font("Arial", 14, QFont::Normal);
	QFontMetrics fMetrics(font);

	m_nLeftMargin = fMetrics.width(QString::number(m_nMaxFrequencyCount)) + 27;
	m_nRightMargin = fMetrics.width(QString::number(m_nMax)) / 2;
	m_nTopMargin = fMetrics.height();
	m_nBottomMargin = fMetrics.height() * 2;

	m_nWidth -= m_nLeftMargin;
	m_nHeight -= m_nBottomMargin;

	qDebug() << "Plot";
	qDebug() << "Height: " << width();
	qDebug() << "Width: " << height();

	QWidget::resizeEvent(pEvent);
}

void CPlot::paintEvent(QPaintEvent *pEvent)
{
	Q_UNUSED(pEvent);

	clear();

	QPainter painter(this);

	painter.translate(m_nLeftMargin, m_nHeight);

	//drawHeader(&painter);
	drawPlot(&painter);
	//drawFooter(&painter);
}

void CPlot::drawPlot(QPainter *pPainter)
{
	drawAxes(pPainter);
	drawBins(pPainter);
}

void CPlot::drawAxes(QPainter *pPainter)
{
	pPainter->save();

	QFont font("Arial", 14, QFont::Normal);
	pPainter->setPen(QPen(Qt::black, 2, Qt::SolidLine));
	pPainter->setFont(font);
	QFontMetrics fMetrics(font);

	m_nHeight -= m_nTopMargin;
	m_nWidth -= m_nRightMargin;

	int nYOffset = m_nHeight / 9;

	// Y axis
	pPainter->drawLine(QLine(0, 0, 0, -m_nHeight));

	for (int nY = 0, nYCordinate = 0; nY <= m_nHeight; nY += nYOffset, nYCordinate += m_nYCordinatesOffset)
	{
		int nTextWidth = fMetrics.width(QString::number(nYCordinate));
		int nTextHeight = fMetrics.height();

		// draw Y cordinates
		pPainter->drawLine(QLine(-5, -nY, 5, -nY));
		pPainter->drawText(-10, -( nY + int(nTextHeight / 2) ), -(nTextWidth + 10), nTextHeight, Qt::AlignCenter, QString::number(nYCordinate));
	}

	// X axis
	pPainter->drawLine(QLine(0, 0, m_nWidth, 0));

	int nXOffset = qCeil(m_nWidth / m_nBinsCount);
	int nXCordinatesOffset = m_nBinsWidth;

	for (int nX = 0, nXCordinate = m_nMin; nX <= m_nWidth; nX += nXOffset, nXCordinate += nXCordinatesOffset)
	{
		int nTextWidth = fMetrics.width(QString::number(nXCordinate));
		int nTextHeight = fMetrics.height();

		if ((nX + nXOffset) <= m_nWidth)
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

void CPlot::drawBins(QPainter *pPainter)
{
	pPainter->save();

	pPainter->setPen(QPen(Qt::black, 1, Qt::SolidLine));
	pPainter->setOpacity(0.6);
	pPainter->setBrush(Qt::blue);

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
		int height = -((nHeight * qCeil(m_nHeight / 9)) / m_nYCordinatesOffset);
	
		pPainter->drawRect(nWidth.first, 0, nWidth.second, height);
		
	}

	pPainter->restore();
}

void CPlot::drawHeader(QPainter *pPainter)
{
	pPainter->save();
	
	QRect rect(0, 0, m_nWidth, 80);

	QFont font("Arial", 36, QFont::Normal);
	pPainter->setPen(QPen(Qt::darkGray, 2, Qt::SolidLine));
	pPainter->setOpacity(0.1);
	pPainter->drawRect(rect);
	pPainter->setOpacity(1);
	pPainter->setFont(font);
	pPainter->drawText(rect, Qt::AlignCenter, "CPlot");

	pPainter->restore();
}

void CPlot::drawFooter(QPainter *pPainter)
{
	pPainter->save();
	
	QRect rect(0, 0, m_nWidth, -40);

	pPainter->translate(0, m_nHeight);
	QFont font("Arial", 24, QFont::Normal);
	pPainter->setPen(QPen(Qt::darkGray, 3, Qt::SolidLine));
	pPainter->setOpacity(0.1);
	pPainter->drawRect(rect);
	pPainter->setOpacity(1);
	pPainter->setFont(font);
	pPainter->setPen(QPen(Qt::darkGray, 3, Qt::SolidLine));
	pPainter->drawText(rect, Qt::AlignCenter, "CPlot");

	pPainter->restore();
}

void CPlot::clear()
{
	for (auto &pBin : m_lstBins)
	{
		if (pBin != nullptr)
			delete pBin;
	}

	m_lstBins.clear();
}

void CPlot::run()
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

	m_nYCordinatesOffset = qCeil(m_nMaxFrequencyCount / 9.0);
}

CPlot::CBin::CBin(int nX1, int nX2) : m_nBinHeight(0), m_pRange(nullptr)
{
	m_nBinWidth = QPair<int, int>(nX1, nX2);
}

CPlot::CBin::~CBin()
{
	if (m_pRange != nullptr)
		delete m_pRange;
}


int CPlot::CBin::getHeight()
{
	return m_nBinHeight;
}

QPair<int, int> CPlot::CBin::getWidth()
{
	return m_nBinWidth;
}

void CPlot::CBin::increaseHeight(int nVal)
{
	m_nBinHeight += nVal;
}

void CPlot::CBin::setRange(int nLow, int nHigh)
{
	m_pRange = new CRange(nLow, nHigh);
}

CPlot::CRange* CPlot::CBin::getRange()
{
	return m_pRange;
}

CPlot::CRange::CRange(int nLow, int nHigh) : m_nLow(nLow), m_nHigh(nHigh) {}

bool CPlot::CRange::inRange(int nValue)
{
	return (unsigned(nValue - m_nLow) <= m_nHigh - m_nLow);
}

CHistogram::CHistogram(QVector<int> vectData, QWidget *pParent) 
	: m_vectData(vectData), QWidget(pParent), m_pPlot(nullptr)
{
	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	
	//setStyleSheet("border: 1px solid black;");

	QHBoxLayout *pLayout = new QHBoxLayout();
	setLayout(pLayout);

	m_pPlot = new CPlot(m_vectData);

	pLayout->addWidget(m_pPlot);
}

CHistogram::~CHistogram()
{
}

void CHistogram::resizeEvent(QResizeEvent *pEvent)
{
	if (m_pPlot != nullptr)
	{
		qDebug() << "Histogram";
		qDebug() << "Height: " << width();
		qDebug() << "Width: " << height();
	}

	QWidget::resizeEvent(pEvent);
}

void CHistogram::wheelEvent(QWheelEvent *pEvent)
{
	m_pPlot->update();
	QWidget::wheelEvent(pEvent);
}

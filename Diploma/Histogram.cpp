#include "Histogram.h"
#include <QPainter>
#include <QtMath>
#include <QFontMetrics>
#include <QHBoxLayout>
#include "HistogramPaneWidget.h"
#include "HistogramPainter.h"

CHistogram::CHistogram(t_sHistogramData const &oHistogramData, CHistogramPainter *pHistogramPainter, QWidget *pParent)
	: m_oHistogramData(oHistogramData),
	  m_pHistogramPainter(pHistogramPainter), 
	  m_bIsCalculated(false), 
	  QWidget(pParent)
{
	installEventFilter(pParent);
	//run();
}

CHistogram::~CHistogram() {}

void CHistogram::updateConfig()
{
	m_oCfg.nHeight = this->height();
	m_oCfg.nWidth = this->width();

	QFont font("Arial", 14, QFont::Normal);
	QFontMetrics fMetrics(font);

	m_oCfg.nLeftMargin = fMetrics.width(QString::number(m_oCfg.nMaxFrequencyCount)) + 25;
	m_oCfg.nRightMargin = fMetrics.width(QString::number(m_oCfg.nMaxValue)) / 2 + 10;
	m_oCfg.nTopMargin = fMetrics.height();
	m_oCfg.nBottomMargin = fMetrics.height() * 2;

	m_oCfg.nWidth -= m_oCfg.nLeftMargin;
	m_oCfg.nHeight -= m_oCfg.nBottomMargin;
}

t_sHistogramConfig CHistogram::getConfig() const
{
	return m_oCfg;
}

void CHistogram::paintEvent(QPaintEvent *pEvent)
{
	Q_UNUSED(pEvent);

	updateConfig();
	QPainter painter(this);
	m_pHistogramPainter->setTitle("Histogram Title");
	m_pHistogramPainter->draw(&painter, m_oHistogramData, rect());
}

void CHistogram::run()
{
	if (m_aData.isEmpty())
		return;

	for (int i = 0; i < m_aData.count(); i++)
	{
		QMap<int, int>::iterator iter = m_oCfg.mapFrequency.find(m_aData[i]);
		if (iter != m_oCfg.mapFrequency.end())
		{
			iter.value()++;
			if (iter.value() > m_oCfg.nMaxFrequencyCount)
				m_oCfg.nMaxFrequencyCount = iter.value();
		}
		else
			m_oCfg.mapFrequency.insert(m_aData[i], 1);
	}
	// Sturge’s Rule 
	// https://www.statisticshowto.datasciencecentral.com/choose-bin-sizes-statistics/
	m_oCfg.nBinsCount = qFloor(1 + 3.22 * log(m_aData.count()));
	int nBinsCount = 1 + 3.22 * log(m_aData.count());

	if (m_oCfg.nMaxFrequencyCount < 9)
		m_oCfg.nMaxFrequencyCount = 9;

	if (m_oCfg.nBinsCount > 20)
		m_oCfg.nBinsCount = 20;

	else if (m_oCfg.nBinsCount < 5)
		m_oCfg.nBinsCount = 5;

	m_oCfg.nMinValue = m_oCfg.mapFrequency.firstKey();
	m_oCfg.nMaxValue = m_oCfg.mapFrequency.lastKey();

	m_oCfg.nBinsWidth = qCeil((m_oCfg.nMaxValue - m_oCfg.nMinValue) / (double)m_oCfg.nBinsCount);
	int nBinsRange = qCeil((m_oCfg.nMaxValue - m_oCfg.nMinValue) / (double)m_oCfg.nBinsCount);
	
	QVector<int> aHistogramData(nBinsCount);
	for (int i = 0; i < m_aData.count(); i++)
	{
		int nIndex = (m_aData[i] - m_oCfg.nMinValue) / nBinsRange;
		if (nIndex > i)
			nIndex = i;
	}

	m_oCfg.nYCordinatesOffset = qCeil(m_oCfg.nMaxFrequencyCount / 9.0);

	m_bIsCalculated = true;
}
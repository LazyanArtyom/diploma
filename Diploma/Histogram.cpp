#include "Histogram.h"
#include "HistogramPainter.h"
#include <QPainter>
#include <QtMath>
#include <QFontMetrics>
#include <QDebug>
#include <QHBoxLayout>
#include <QApplication>

CHistogram::CHistogram(QVector<int> vectData, CHistogramPainter *pHistogramPainter, QWidget *pParent) 
	: m_vectData(vectData), m_pHistogramPainter(pHistogramPainter), QWidget(pParent)
{
	installEventFilter(pParent);
	run();
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

t_sHistogramConfig CHistogram::getConfig()
{
	return m_oCfg;
}

void CHistogram::paintEvent(QPaintEvent *pEvent)
{
	Q_UNUSED(pEvent);

	updateConfig();
	QPainter painter(this);
	m_pHistogramPainter->draw(&painter, m_oCfg);
}

void CHistogram::run()
{
	if (m_vectData.isEmpty())
		return;

	for (int i = 0; i < m_vectData.count(); i++)
	{
		QMap<int, int>::iterator iter = m_oCfg.mapFrequency.find(m_vectData[i]);
		if (iter != m_oCfg.mapFrequency.end())
		{
			iter.value()++;
			if (iter.value() > m_oCfg.nMaxFrequencyCount)
				m_oCfg.nMaxFrequencyCount = iter.value();
		}
		else
			m_oCfg.mapFrequency.insert(m_vectData[i], 1);
	}

	m_oCfg.nBinsCount = qFloor(1 + 3.22 * log(m_vectData.count()));

	if (m_oCfg.nMaxFrequencyCount < 9)
		m_oCfg.nMaxFrequencyCount = 9;

	if (m_oCfg.nBinsCount > 20)
		m_oCfg.nBinsCount = 20;

	else if (m_oCfg.nBinsCount < 5)
		m_oCfg.nBinsCount = 5;

	m_oCfg.nMinValue = m_oCfg.mapFrequency.firstKey();
	m_oCfg.nMaxValue = m_oCfg.mapFrequency.lastKey();

	m_oCfg.nBinsWidth = qCeil((m_oCfg.nMaxValue - m_oCfg.nMinValue) / (double)m_oCfg.nBinsCount);

	m_oCfg.nYCordinatesOffset = qCeil(m_oCfg.nMaxFrequencyCount / 9.0);

	m_oCfg.bIsCalculated = true;
}
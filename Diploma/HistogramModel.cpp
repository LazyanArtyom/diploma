#include "HistogramModel.h"
#include <QtMath>
#include <QThread>

CHistogramModel::CHistogramModel() : m_aData(QVector<int>()), m_nDataCount(0)
{
}

CHistogramModel::~CHistogramModel()
{
}

void CHistogramModel::setData(QVector<int> aData)
{
	m_aData = aData;
	m_nDataCount = m_aData.count();
}

t_sHistogramData CHistogramModel::run()
{
	t_sHistogramData oHistogramData;

	if (m_aData.isEmpty())
		return oHistogramData;

	// Sturge’s Rule 
	// https://www.statisticshowto.datasciencecentral.com/choose-bin-sizes-statistics/
	oHistogramData.nBinsCount = qFloor(1 + 3.22 * log(m_nDataCount));

	if (oHistogramData.nBinsCount > 20)
		oHistogramData.nBinsCount = 20;
	else if (oHistogramData.nBinsCount < 5)
		oHistogramData.nBinsCount = 5;

	oHistogramData.nMaxValue = m_aData[0];
	oHistogramData.nMinValue = m_aData[0];

	for (int i = 1; i < m_nDataCount; i++)
	{
		if (m_aData[i] < oHistogramData.nMinValue)
			oHistogramData.nMinValue = m_aData[i];
		if (m_aData[i] > oHistogramData.nMaxValue)
			oHistogramData.nMaxValue = m_aData[i];
	}

	oHistogramData.nBinsRange = qCeil((oHistogramData.nMaxValue - oHistogramData.nMinValue) / (double)oHistogramData.nBinsCount);
	
	oHistogramData.aFrequencyTable = calculateFrequencyTableSingleThread(m_nDataCount, oHistogramData.nMinValue, oHistogramData.nBinsCount, oHistogramData.nBinsRange);

	return oHistogramData;
}

QVector<int> CHistogramModel::calculateFrequencyTableSingleThread(int nDataCount, int nMinValue, int nBinsCount, int nBinsRange)
{
	QVector<int> aFrequencyTable;
	aFrequencyTable.resize(nBinsCount);


	for (int i = 0; i < nDataCount; i++)
	{
		int nIndex = (m_aData[i] - nMinValue) / nBinsRange;
		if (nIndex > (nBinsCount - 1))
			nIndex = (nBinsCount - 1);
		aFrequencyTable[nIndex]++;
	}
	return aFrequencyTable;
}

QVector<int> CHistogramModel::calculateFrequencyTableMultiThread(int nDataCount, int nMinValue, int nBinsCount, int nBinsRange)
{
	int nThreadCount = QThread::idealThreadCount();

	int nBegin = 0;
	int nEnd = 0;
	int nOffset = m_nDataCount / nThreadCount;

	for (int i = 0; i < nThreadCount; i++)
	{

	}
}

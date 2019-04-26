#include <QtMath>
#include <QThread>
#include <QFutureSynchronizer>
#include <QtConcurrent/qtconcurrentrun.h>

// Local includes
#include "ChartModel.h"

////////////////////////////////////////////////////////////////////////////////
//
//	CHistogramModel
//
IChartData* CHistogramModel::run(QVector<double> aNumericValues, bool bMultithread)
{
	m_aNumericValues.clear();
	m_aNumericValues = aNumericValues;

	m_nDataCount = m_aNumericValues.count();

	if (m_aNumericValues.isEmpty())
		return nullptr;

	m_nDataCount = m_aNumericValues.count();

	m_pHistogramData = new CHistogramData();

	if (m_nBinCount == 0)
	{
		// Sturge’s Rule 
		// https://www.statisticshowto.datasciencecentral.com/choose-bin-sizes-statistics/
		m_pHistogramData->nBinsCount = qFloor(1 + 3.22 * log(m_nDataCount));

		if (m_pHistogramData->nBinsCount > 20)
			m_pHistogramData->nBinsCount = 20;
		else if (m_pHistogramData->nBinsCount < 5)
			m_pHistogramData->nBinsCount = 5;
	}
	else
		m_pHistogramData->nBinsCount = m_nBinCount;

	// calculate Min and Max values
	m_pHistogramData->nMaxValue = m_aNumericValues[0];
	m_pHistogramData->nMinValue = m_aNumericValues[0];
	for (int i = 1; i < m_nDataCount; i++)
	{
		if (m_aNumericValues[i] < m_pHistogramData->nMinValue)
			m_pHistogramData->nMinValue = m_aNumericValues[i];
		if (m_aNumericValues[i] > m_pHistogramData->nMaxValue)
			m_pHistogramData->nMaxValue = m_aNumericValues[i];
	}

	// BinRange = qCeil(Max - Min) / BinCount
	m_pHistogramData->nBinsRange = qCeil((m_pHistogramData->nMaxValue - m_pHistogramData->nMinValue)
		/ (double)m_pHistogramData->nBinsCount);
	
	if (bMultithread)
		m_pHistogramData->aFrequencyTable = calculateFrequencyTableMultiThread();
	else
		m_pHistogramData->aFrequencyTable = calculateFrequencyTableSingleThread();

	return m_pHistogramData;
}

void CHistogramModel::setBinCount(int nCount)
{
	m_nBinCount = nCount;
}

QVector<int> CHistogramModel::calculateFrequencyTableSingleThread()
{
	QVector<int> aFrequencyTable;
	aFrequencyTable.resize(m_pHistogramData->nBinsCount);

	// index = (CurrentValue - MinValue) / BinRange
	for (int i = 0; i < m_nDataCount; i++)
	{
		int nIndex = (m_aNumericValues[i] - m_pHistogramData->nMinValue) / m_pHistogramData->nBinsRange;
		if (nIndex > (m_pHistogramData->nBinsCount - 1))
			nIndex = (m_pHistogramData->nBinsCount - 1);
		aFrequencyTable[nIndex]++;
	}
	return aFrequencyTable;
}

QVector<int> CHistogramModel::calculate(int nBegin, int nEnd)
{
	QVector<int> localResult;
	localResult.resize(m_pHistogramData->nBinsCount);

	for (int i = nBegin; i < nEnd; ++i)
	{
		int nIndex = (m_aNumericValues[i] - m_pHistogramData->nMinValue) / m_pHistogramData->nBinsRange;
		if (nIndex > (m_pHistogramData->nBinsCount - 1))
			nIndex = (m_pHistogramData->nBinsCount - 1);

		if (nIndex < 0)
			nIndex = 0;

		localResult[nIndex]++;
	}

	return localResult;
}

QVector<int> CHistogramModel::calculateFrequencyTableMultiThread()
{
	QVector<int> aFrequencyTable;
	aFrequencyTable.resize(m_pHistogramData->nBinsCount);

	int nThreadCount = QThread::idealThreadCount();
	int nOffset = m_nDataCount / nThreadCount;

	QFutureSynchronizer<QVector<int> > oSynchronizer;

	for (int nBegin = 0; nBegin < m_nDataCount; nBegin += nOffset)
	{
		int nEnd = nBegin + nOffset;

		if (nEnd > m_nDataCount)
			nEnd = m_nDataCount;

		oSynchronizer.addFuture( QtConcurrent::run( this, &CHistogramModel::calculate, nBegin, nEnd) );
	}

	oSynchronizer.waitForFinished();

	for (int i = 0; i < oSynchronizer.futures().count(); ++i)
	{
		QVector<int> aTemp = oSynchronizer.futures().at(i).result();
		for (int j = 0; j < aTemp.count(); ++j)
			aFrequencyTable[j] += aTemp[j];
	}

	oSynchronizer.clearFutures();

	return aFrequencyTable;
}
////////////////////////////////////////////////////////////////////////////////
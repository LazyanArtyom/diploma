#include "HistogramModel.h"
#include <QtMath>

CHistogramModel::CHistogramModel()
{
}

CHistogramModel::~CHistogramModel()
{
}

void CHistogramModel::setData(QVector<int> aData)
{
	m_aData = aData;
}

t_sHistogramData CHistogramModel::run()
{
	t_sHistogramData oHistogramData;

	if (m_aData.isEmpty())
		return oHistogramData;

	int nDataCount = m_aData.count();

	// Sturge’s Rule 
	// https://www.statisticshowto.datasciencecentral.com/choose-bin-sizes-statistics/
	oHistogramData.nBinsCount = qFloor(1 + 3.22 * log(m_aData.count()));

	if (oHistogramData.nBinsCount > 20)
		oHistogramData.nBinsCount = 20;
	else if (oHistogramData.nBinsCount < 5)
		oHistogramData.nBinsCount = 5;

	oHistogramData.nMaxValue = m_aData[0];
	oHistogramData.nMinValue = m_aData[0];
	for (int i = 1; i < nDataCount; i++)
	{
		if (m_aData[i] < oHistogramData.nMinValue)
			oHistogramData.nMinValue = m_aData[i];
		if (m_aData[i] > oHistogramData.nMaxValue)
			oHistogramData.nMaxValue = m_aData[i];
	}

	oHistogramData.nBinsRange = qCeil((oHistogramData.nMaxValue - oHistogramData.nMinValue) / (double)oHistogramData.nBinsCount);

	oHistogramData.aFrequencyTable.resize(oHistogramData.nBinsCount);
	for (int i = 0; i < m_aData.count(); i++)
	{
		int nIndex = (m_aData[i] - oHistogramData.nMinValue) / oHistogramData.nBinsRange;
		if (nIndex > (oHistogramData.nBinsCount - 1))
			nIndex = (oHistogramData.nBinsCount - 1);
		oHistogramData.aFrequencyTable[nIndex]++;
	}

	return oHistogramData;
}

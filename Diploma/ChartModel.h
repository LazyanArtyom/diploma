#ifndef ChartModel_H
#define ChartModel_H

//	Loclal includes
#include "Definitions.h"

////////////////////////////////////////////////////////////////////////////////
//
//	IChartModel
//
class IChartModel
{
public:
	virtual ~IChartModel() = default;
	virtual IChartData* run(QVector<double> aData, bool bMultithread = false) = 0;
};
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
//	CHistogramModel
//
class CHistogramModel : public IChartModel
{
public:
	//
	//! IChartModel Interface
	//
	IChartData* run(QVector<double> aNumericValues, bool bMultithread = false) override;

public:
	void setBinCount(int nCount);

protected:
	QVector<int> calculate(int nBegin, int nEnd);
	QVector<int> calculateFrequencyTableMultiThread();
	QVector<int> calculateFrequencyTableSingleThread();

private:
	int m_nBinCount = 0;
	int m_nDataCount = 0;

	EChartType       m_eType;
	CHistogramData*	 m_pHistogramData;
	QVector<double>  m_aNumericValues;
};
////////////////////////////////////////////////////////////////////////////////

#endif // ChartModel_H

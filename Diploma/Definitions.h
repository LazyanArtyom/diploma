#ifndef Definitions_H
#define Definitions_H

#include <QVector>

//////////////////////////////////////////////////////////////
//
//	Data Types
//
enum class EChartType
{
	Histogram
};

struct IChartData
{
	QString sName;
	EChartType eType;
	virtual ~IChartData() = default;
};

struct CHistogramData : public IChartData
{
	int    nBinsCount = 0;
	double nMinValue = 0.0;
	double nMaxValue = 0.0;
	double nBinsRange = 0.0;
	QVector<int> aFrequencyTable = QVector<int>();
};
//////////////////////////////////////////////////////////////

#endif // Definitions_H
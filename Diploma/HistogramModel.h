#ifndef HistogramModel_H
#define HistogramModel_H

#include <QVector>

typedef struct SHistogramData
{
	int nBinsCount;
	int nBinsRange;
	int nMinValue;
	int nMaxValue;
	QVector<int> aFrequencyTable;

	inline SHistogramData()
		: nBinsCount(0),
		  nBinsRange(0),
		  nMinValue(0),
		  nMaxValue(0),
		  aFrequencyTable(QVector<int>())
	{}

} t_sHistogramData;

class CHistogramModel
{
public:
	CHistogramModel();
	~CHistogramModel();

	void setData(QVector<int> aData);
	t_sHistogramData run();
	QVector<int> calculateFrequencyTableSingleThread(int nDataCount, int nMinValue, int nBinsCount, int nBinsRange);
	QVector<int> calculateFrequencyTableMultiThread(int nDataCount, int nMinValue, int nBinsCount, int nBinsRange);

private:
	QVector<int> m_aData;
	int m_nDataCount;
};

#endif // HistogramModel_H

#ifndef Histogram_H
#define Histogram_H

#include <QWidget>
#include <QPaintEvent>

class CHistogramPainter;

typedef struct SHistogramConfig
{
	int nWidth;
	int nHeight;
	int nLeftMargin;
	int nRightMargin;
	int nTopMargin;
	int nBottomMargin;
	int nBinsCount;
	int nMaxFrequencyCount;
	int nBinsWidth;
	int nMinValue;
	int nMaxValue;
	int nYCordinatesOffset;
	bool bIsCalculated;
	QMap<int, int> mapFrequency;

	inline SHistogramConfig()
		:nWidth(400),
		nHeight(400),
		nLeftMargin(0),
		nRightMargin(),
		nTopMargin(),
		nBottomMargin(),
		nBinsCount(5),
		nMaxFrequencyCount(10),
		nBinsWidth(0),
		nMinValue(0),
		nMaxValue(10),
		nYCordinatesOffset(2),
		bIsCalculated(false),
		mapFrequency(QMap<int, int>())
	{}

} t_sHistogramConfig;

class CHistogram final : public QWidget
{
public:
	CHistogram(QVector<int> vectData, CHistogramPainter *pHistogramPainter, QWidget *pParent = 0);
	~CHistogram();

	void updateConfig();
	t_sHistogramConfig getConfig();

protected:
	void paintEvent(QPaintEvent *pEvent);

private:
	t_sHistogramConfig m_oCfg;
	CHistogramPainter *m_pHistogramPainter;

	void run();

private:
	QVector<int> m_vectData;

};
#endif // Histogram_H


#ifndef HistogramPainter_H
#define HistogramPainter_H

#include <QList>
#include <QPainter>
#include "Histogram.h"
#include "HistogramModel.h"

class CHistogramPainter
{
public:
	CHistogramPainter();
	~CHistogramPainter();

	void draw(QPainter *pPainter, t_sHistogramData &oHistogramData, QRect rect);
	void drawPlot(QPainter *pPainter);
	void drawAxes(QPainter *pPainter);
	void drawBin(QPainter *pPainter, int nBinIndex, QPair<int, int> range, int nScale);
	void drawHeader(QPainter *pPainter);
	void drawFooter(QPainter *pPainter);

	void setTitle(const QString sTitle);

private:
	t_sHistogramData m_oHistogramData;
	t_sHistogramConfig m_oCfg;
	QString m_sTitle;

	int m_nLeftMargin;
	int m_nRightMargin;
	int m_nTopMargin;
	int m_nBottomMargin;

	int m_nHeaderHeight;
	int m_nFooterHeight;

	QRect m_oRect;
};

#endif


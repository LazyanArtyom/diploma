#ifndef HistogramPainter_H
#define HistogramPainter_H

#include <QList>
#include <QPainter>
#include "Histogram.h"
#include "HistogramModel.h"

class CBin;
class CRange;

class CHistogramPainter
{
public:
	CHistogramPainter();
	~CHistogramPainter();

	void draw(QPainter *pPainter, t_sHistogramData &oHistogramData, QRect rect);
	void drawPlot(QPainter *pPainter);
	void drawAxes(QPainter *pPainter);
	void drawBins(QPainter *pPainter);
	void drawBin(QPainter *pPainter, int nX1, int nX2, int nIndex);
	void drawHeader(QPainter *pPainter);
	void drawFooter(QPainter *pPainter);

	void setTitle(const QString sTitle);

	void clear();

private:
	t_sHistogramData m_oHistogramData;
	t_sHistogramConfig m_oCfg;
	QList<CBin*> m_lstBins;
	//QVector<int> m_aHistoData;

	QString m_sTitle;

	int m_nLeftMargin;
	int m_nRightMargin;
	int m_nTopMargin;
	int m_nBottomMargin;

	int m_nHeaderHeight;
	int m_nFooterHeight;

	QRect m_oRect;
};

class CRange
{
public:
	CRange(int nLow, int nHigh);
	bool inRange(int nValue);

private:
	int m_nLow;
	int m_nHigh;
};

class CBin
{
public:
	CBin(int nX1, int nX2);
	~CBin();

	int getHeight();
	QPair<int, int> getWidth();

	void increaseHeight(int nVal);

	void setRange(int nLow, int nHigh);
	CRange* getRange();

private:
	QPair<int, int> m_nBinWidth;
	int m_nBinHeight;
	CRange* m_pRange;
};

#endif


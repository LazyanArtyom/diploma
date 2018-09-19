#ifndef HistogramPainter_H
#define HistogramPainter_H

#include <QList>
#include <QPainter>
#include "Histogram.h"

class CBin;
class CRange;

class CHistogramPainter
{
public:
	CHistogramPainter();
	~CHistogramPainter();

	void draw(QPainter *pPainter, t_sHistogramConfig &oCfg);
	void drawPlot(QPainter *pPainter);
	void drawAxes(QPainter *pPainter);
	void drawBins(QPainter *pPainter);
	void drawHeader(QPainter *pPainter);
	void drawFooter(QPainter *pPainter);

	void clear();

private:
	t_sHistogramConfig m_oCfg;
	QList<CBin*> m_lstBins;
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


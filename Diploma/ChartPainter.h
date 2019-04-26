#ifndef ChartPainter_H
#define ChartPainter_H

#include <QList>
#include <QPainter>

// Local includes
#include "Definitions.h"

////////////////////////////////////////////////////////////////////////////////
//
//	IPainter
//
class IPainter
{
public:
	virtual ~IPainter() = default;
	virtual void draw(QPainter* pPainter, IChartData* pChartData, QRect rect) = 0;
};
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
//	CHistogramPainter
//
class CHistogramPainter : public IPainter
{
public:
	CHistogramPainter();

public:
	//
	//! IPainter Interface
	//
	void draw(QPainter* pPainter, IChartData* pChartData, QRect rect) override;

protected:
	void drawAxes(QPainter* pPainter);
	void drawPlot(QPainter* pPainter);
	void drawHeader(QPainter* pPainter);
	void drawFooter(QPainter* pPainter);
	void drawBin(QPainter* pPainter, int nBinIndex, QPair<int, int> range, double nScale);

private:
	int m_nTopMargin;
	int m_nLeftMargin;
	int m_nRightMargin;
	int m_nBottomMargin;
	int m_nHeaderHeight;
	int m_nFooterHeight;

	QRect m_oRect;
	CHistogramData* m_oHistogramData;
};
////////////////////////////////////////////////////////////////////////////////

#endif // ChartPainter_H


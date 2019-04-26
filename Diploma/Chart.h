#ifndef Chart_H
#define Chart_H

#include <QWidget>
#include <QPaintEvent>

//	Loclal includes
#include "Definitions.h"


class CHistogramPainter;

////////////////////////////////////////////////////////////////////////////////
//
//	IChart
//
class IChart : public QWidget
{
public:
	IChart(QWidget *pParent = nullptr) : QWidget(pParent) {}
};
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
//	CHistogram
//
class CHistogram : public IChart
{
public:
	CHistogram(CHistogramData* pHistogramData, CHistogramPainter* pHistogramPainter, QWidget *pParent = nullptr);
	~CHistogram();

protected:
	void paintEvent(QPaintEvent *pEvent);

private:
	CHistogramData*    m_pHistogramData = nullptr;
	CHistogramPainter* m_pHistogramPainter = nullptr;
};
////////////////////////////////////////////////////////////////////////////////

#endif // Chart_H


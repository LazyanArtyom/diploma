#ifndef HISTOGRAMPANEWIDGET_H
#define HISTOGRAMPANEWIDGET_H

#include <QWidget>
#include <QScrollArea>
#include "Histogram.h"

class HistogramPaneWidget : public QScrollArea
{
public:
	HistogramPaneWidget(QWidget *parent = 0);
	~HistogramPaneWidget();

private:
	CPlot *m_pHistogram;
};

#endif // HISTOGRAMPANEWIDGET_H

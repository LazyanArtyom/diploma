#ifndef HISTOGRAMPANEWIDGET_H
#define HISTOGRAMPANEWIDGET_H

#include <QWidget>
#include "Histogram.h"

class HistogramPaneWidget : public QWidget
{
public:
	HistogramPaneWidget(QWidget *parent = 0);
	~HistogramPaneWidget();

private:
	CHistogram *m_pHistogram;
};

#endif // HISTOGRAMPANEWIDGET_H

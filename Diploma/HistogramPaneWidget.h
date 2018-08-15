#ifndef HISTOGRAMPANEWIDGET_H
#define HISTOGRAMPANEWIDGET_H

#include <QTableView>
#include "HistogramModel.h"

class HistogramPaneWidget : public QTableView
{
public:
	HistogramPaneWidget(QWidget *parent = 0);
	~HistogramPaneWidget();

private:
	HistogramModel *m_pModel;
};

#endif // HISTOGRAMPANEWIDGET_H

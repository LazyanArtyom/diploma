#ifndef HistogramController_H
#define HistogramController_H

#include <QVector>
#include "HistogramModel.h"
#include "HistogramPainter.h"
#include "HistogramPaneWidget.h"
#include "HistogramReviewPaneWidget.h"

class CHistogramController
{
public:
	CHistogramController();
	~CHistogramController();

	void init(QVector<int> aData);
	CHistogramPaneWidget* getHistogramPane();
	CHistogramReviewPaneWidget* getHistogramReviewPane();

private:
	CHistogramModel *m_pHistogramModel;
	CHistogramPaneWidget *m_pHistogramPaneWidget;
	CHistogramReviewPaneWidget *m_pHistogramReviewPaneWidget;
	CHistogramPainter *m_pHistogramPainter;
};

#endif // HistogramController_H


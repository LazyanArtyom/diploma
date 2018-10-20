#ifndef HistogramPaneWidget_H
#define HistogramPaneWidget_H

#include <QWidget>
#include <QGridLayout>
#include "flowLayout.h"
#include "Histogram.h"
#include "HistogramModel.h"

class CHistogramPainter;

class CHistogramPaneWidget : public QWidget
{
	Q_OBJECT
public:
	CHistogramPaneWidget(QWidget *pParent = 0);
	~CHistogramPaneWidget();

	void setPainter(CHistogramPainter *pPainter);
	CHistogramPainter* getPainter() const;

	void addHistogram(t_sHistogramData const &oHistogramData);

	void updateGeometry();

protected:
	bool eventFilter(QObject *pObj, QEvent *pEvent);

private:
	CHistogramPainter *m_pHistogramPainter;
	QGridLayout *m_pLayout;

	t_sHistogramData m_oHistogramData;

signals:
	void sigHistogramChecked(t_sHistogramData &oHistogramData);
};

#endif // HistogramPaneWidget_H

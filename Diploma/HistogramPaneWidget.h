#ifndef HistogramPaneWidget_H
#define HistogramPaneWidget_H

#include <QWidget>
#include <QGridLayout>
#include "flowLayout.h"
#include "Histogram.h"

class CHistogramPainter;

class CHistogramPaneWidget : public QWidget
{
	Q_OBJECT
public:
	CHistogramPaneWidget(QWidget *pParent = 0);
	~CHistogramPaneWidget();

	void init();

	void setPainter(CHistogramPainter *pPainter);
	CHistogramPainter* getPainter() const;

	void updateGeometry();

protected:
	bool eventFilter(QObject *pObj, QEvent *pEvent);

private:
	CHistogramPainter *m_pHistogramPainter;
	QGridLayout *m_pLayout;

signals:
	void sigHistogramChecked(t_sHistogramConfig &oCfg);
};

#endif // HistogramPaneWidget_H

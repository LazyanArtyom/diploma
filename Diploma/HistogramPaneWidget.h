#ifndef HistogramPaneWidget_H
#define HistogramPaneWidget_H

#include <QWidget>
#include <QGridLayout>

#include "HistogramDialogBox.h"

class CHistogramPainter;

class CHistogramPaneWidget : public QWidget
{
public:
	CHistogramPaneWidget(QWidget *pParent = 0);
	~CHistogramPaneWidget();

	void init();

protected:
	bool eventFilter(QObject * pObj, QEvent *pEvent);

private:
	CHistogramDialogBox *m_pHistogramDialogBox;
	CHistogramPainter *m_pHistogramPainter;
	QGridLayout *m_pLayout;
};

#endif // HistogramPaneWidget_H

#ifndef MainWorkspaceWidget_H
#define MainWorkspaceWidget_H

#include <QWidget>
#include <QSplitter>

#include "SpreadSheetPaneWidget.h"
#include "ColSelectorWidget.h"
#include "HistogramPaneWidget.h"
#include "HistogramReviewPaneWidget.h"
#include "HistogramPainter.h"

class MainWorkspaceWidget : public QSplitter
{
	Q_OBJECT
public:
	MainWorkspaceWidget(QWidget *parent = 0);
	~MainWorkspaceWidget();
private:
	void setupUi();

	//SpreadSheetPaneWidget *m_pSpreadsheetPaneWidget;
	CHistogramPaneWidget *m_pHistogramPaneWidget;
	CHistogramReviewPaneWidget *m_pHistogramReviewPaneWidget;
	ColSelectorWidget *m_pColSelectorWidget;

	CHistogramPainter *m_pHistogramPainter;
};

#endif // MainWorkspaceWidget_H

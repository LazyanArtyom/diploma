#ifndef MAINWORKSPACEWIDGET_H
#define MAINWORKSPACEWIDGET_H

#include <QWidget>
#include <QSplitter>

#include "SpreadSheetPaneWidget.h"
#include "ColSelectorWidget.h"
#include "HistogramPaneWidget.h"

class MainWorkspaceWidget : public QSplitter
{
	Q_OBJECT
public:
	MainWorkspaceWidget(QWidget *parent = 0);
	~MainWorkspaceWidget();
private:
	void setupUi();

	SpreadSheetPaneWidget *m_pSpreadsheetPaneWidget;
	HistogramPaneWidget *m_pHistogramPaneWidget;
	ColSelectorWidget *m_pColSelectorWidget;
};

#endif

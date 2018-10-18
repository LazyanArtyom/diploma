#ifndef MainWorkspaceWidget_H
#define MainWorkspaceWidget_H

#include "SpreadSheetPaneWidget.h"
#include "ColSelectorWidget.h"
#include "HistogramController.h"

#include <QWidget>
#include <QSplitter>

class MainWorkspaceWidget : public QSplitter
{
	Q_OBJECT
public:
	MainWorkspaceWidget(QWidget *parent = 0);
	~MainWorkspaceWidget();
private:
	void setupUi();

	CHistogramController *m_pHistogramContorller;
	ColSelectorWidget *m_pColSelectorWidget;
};

#endif // MainWorkspaceWidget_H

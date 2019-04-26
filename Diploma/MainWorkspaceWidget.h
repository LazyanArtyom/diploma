//#ifndef CMainWorkspaceWidget_H
//#define CMainWorkspaceWidget_H
//
//#include <QWidget>
//#include <QSplitter>
//#include "ColSelectorWidget.h"
//#include "HistogramController.h"
//#include "SpreadSheetPaneWidget.h"
//
//class CMainWorkspaceWidget : public QSplitter
//{
//	Q_OBJECT
//public:
//	CMainWorkspaceWidget(QWidget *parent = 0);
//	~CMainWorkspaceWidget();
//
//	void setBinCount(int nBinCount);
//	void init();
//
//private:
//	void setupUi();
//
//	ColSelectorWidget*    m_pColSelectorWidget = nullptr;
//	CHistogramController* m_pHistogramContorller = nullptr;
//
//	int  m_nBinCount = 0;
//
//signals:
//	void sigCalculationFinished(int nCalculationTime);
//
//public slots:
//	void onRun();
//};
//
//#endif // CMainWorkspaceWidget_H

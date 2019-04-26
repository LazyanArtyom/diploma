#ifndef MainWindow_H
#define MainWindow_H

#include <QMenuBar>
#include <QComboBox>
#include <QMainWindow>

// Local includes
#include "Timer.h"
#include "ChartController.h"

////////////////////////////////////////////////////////////////////////////////
//
//	CMainWindow
//
class CMainWindow : public QMainWindow
{
	Q_OBJECT
public:
	CMainWindow(QWidget *parent = 0);
	~CMainWindow();

	int  getBinCount() const;
	void setBinCount(int nBinCount);

protected:
	void setupUi();

private slots:
	void onRun();
	void onBinCountChanged(const QString& sText);

private:
	int  m_nBinCount = 0;

	CTimer*    m_pTimer       = nullptr;
	QAction*   m_pRunAct      = nullptr;
	QAction*   m_pOpenAct     = nullptr;
	QToolBar*  m_pToolBar     = nullptr;
	QComboBox* m_pcboBinCount = nullptr;
	CChartController* m_pChartContorller = nullptr;
};
////////////////////////////////////////////////////////////////////////////////

#endif // MainWindow_H
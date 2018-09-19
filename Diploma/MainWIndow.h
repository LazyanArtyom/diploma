#ifndef MainWindow_H
#define MainWindow_H

#include <QMainWindow>
#include <QMenuBar>
#include "MainWorkspaceWidget.h"

class MainWIndow : public QMainWindow
{
	Q_OBJECT
public:
	MainWIndow(QWidget *parent = 0);
	~MainWIndow();
private:
	MainWorkspaceWidget *m_pMainWorkspace;
	QToolBar *m_pToolBar;
	QAction *m_pOpenAct;
	QAction *m_pRunAct;
};

#endif // MainWindow_H
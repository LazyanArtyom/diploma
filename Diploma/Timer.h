#ifndef Timer_H
#define Timer_H

#include <QLabel>
#include <QTimer>

////////////////////////////////////////////////////////////////////////////////
//
//	CTimer
//
class CTimer : public QLabel
{
	Q_OBJECT
public:
	CTimer(QWidget *pParent = 0);

public:
	void stop();
	void start();

public:
	QTimer m_oTimer;
	int m_nCurrentInterval;
};
////////////////////////////////////////////////////////////////////////////////

#endif // Timer_H


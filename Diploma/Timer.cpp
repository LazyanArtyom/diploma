// Local includes
#include "Timer.h"

////////////////////////////////////////////////////////////////////////////////
//
//	CTimer
//
CTimer::CTimer(QWidget *pParent) : m_nCurrentInterval(0), QLabel(pParent)
{
	setText(QString::number(m_nCurrentInterval));
}

void CTimer::start()
{
	m_oTimer.start(10);
}

void CTimer::stop()
{
	m_oTimer.stop();
}
////////////////////////////////////////////////////////////////////////////////
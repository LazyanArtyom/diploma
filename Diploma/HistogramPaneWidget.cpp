#include "HistogramPaneWidget.h"
#include "HistogramPainter.h"

#include <QGridLayout>
#include <QScrollBar>
#include <QApplication>

CHistogramPaneWidget::CHistogramPaneWidget(QWidget *pParent)
	: m_pHistogramPainter(nullptr), QWidget(pParent)
{
	m_pLayout = new QGridLayout();
	setLayout(m_pLayout);

	// for setting layout max or min sizes
	m_pLayout->setSizeConstraint(QLayout::SetMinAndMaxSize);

	m_pLayout->setSpacing(5);
	m_pLayout->setMargin(5);
}

CHistogramPaneWidget::~CHistogramPaneWidget()
{
}

void CHistogramPaneWidget::init()
{
	m_pLayout->setColumnMinimumWidth(0, 300);
	m_pLayout->setColumnMinimumWidth(1, 300);
	for (int i = 0; i < 10; i++)
	{
		QVector<int> vect;
		for (int j = 0; j < 10; j++)
			vect.push_back((qrand() % 99));

		CHistogram *pHistogram = new CHistogram(vect, this);
		m_pLayout->addWidget(pHistogram);
		/*
		if (i == 0)
			emit sigHistogramChecked(pHistogram->getConfig());
			*/

		if (i < 10 / 2)
			m_pLayout->setRowMinimumHeight(i, 300);
	}
}

void CHistogramPaneWidget::setPainter(CHistogramPainter *pPainter)
{
	m_pHistogramPainter = pPainter;
}

CHistogramPainter* CHistogramPaneWidget::getPainter() const
{
	return m_pHistogramPainter;
}

bool CHistogramPaneWidget::eventFilter(QObject *pObj, QEvent *pEvent)
{
	CHistogram *pHistogram = static_cast<CHistogram*>(pObj);

	if (pEvent->type() == QEvent::MouseButtonRelease)
	{		
		emit sigHistogramChecked(pHistogram->getConfig());
	}
	else if (pEvent->type() == QEvent::Enter)
	{
		QApplication::setOverrideCursor(Qt::PointingHandCursor);
		pHistogram->setStyleSheet("border: 3px solid #2980B9;");
	}
	else if (pEvent->type() == QEvent::Leave)
	{
		QApplication::restoreOverrideCursor();
		pHistogram->setStyleSheet("border: 2px solid none;");
	}

	return QWidget::eventFilter(pObj, pEvent);;
}

#include "HistogramPaneWidget.h"
#include "HistogramPainter.h"

#include <QGridLayout>
#include <QScrollBar>
#include <QApplication>

#include <QDebug>

CHistogramPaneWidget::CHistogramPaneWidget(QWidget *pParent)
	: m_pHistogramPainter(nullptr), QWidget(pParent)
{
	m_pLayout = new QGridLayout(this);
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
	updateGeometry();

	//for (int i = 0; i < 10; i++)
	//{
	//	QVector<int> vect;
	//	for (int j = 0; j < 10; j++)
	//		vect.push_back((qrand() % 99));

	//	CHistogram *pHistogram = new CHistogram(vect, this);
	//	m_pLayout->addWidget(pHistogram);
	//}

	QVector<int> vect = {1, 3, 1, 1, 1, 5, 8, 10, 0, 5, 5};
	CHistogram *pHistogram = new CHistogram(vect, this);
	m_pLayout->addWidget(pHistogram);
}

void CHistogramPaneWidget::setPainter(CHistogramPainter *pPainter)
{
	m_pHistogramPainter = pPainter;
}

CHistogramPainter* CHistogramPaneWidget::getPainter() const
{
	return m_pHistogramPainter;
}

void CHistogramPaneWidget::updateGeometry()
{
	int nWidth = width() / 2;
	m_pLayout->setColumnMinimumWidth(0, nWidth);
	m_pLayout->setColumnMinimumWidth(1, nWidth);

	for (int i = 0; i < 10; i++)
	{
		if (i < 10 / 2)
			m_pLayout->setRowMinimumHeight(i, 500);
	}
}

bool CHistogramPaneWidget::eventFilter(QObject *pObj, QEvent *pEvent)
{
	CHistogram *pHistogram = static_cast<CHistogram*>(pObj);

	if (pEvent->type() == QEvent::MouseButtonPress)
	{		
		QMouseEvent *pMouseEvent = static_cast<QMouseEvent*>(pEvent);
		
		if (pMouseEvent->buttons() == Qt::LeftButton)
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

#include "HistogramPaneWidget.h"
#include "HistogramPainter.h"
#include "Histogram.h"

#include <QGridLayout>
#include <QScrollBar>
#include <QMessageBox>
#include <QApplication>
#include <QSize>
#include <QScreen>

CHistogramPaneWidget::CHistogramPaneWidget(QWidget *pParent)
	: m_pHistogramDialogBox(nullptr), m_pHistogramPainter(nullptr), QWidget(pParent)
{
	m_pHistogramPainter = new CHistogramPainter();
	m_pHistogramDialogBox = new CHistogramDialogBox(this);
	m_pHistogramDialogBox->setPainter(m_pHistogramPainter);

	m_pLayout = new QGridLayout();
	setLayout(m_pLayout);

	// for setting layout max or min sizes
	m_pLayout->setSizeConstraint(QLayout::SetMinAndMaxSize);

	m_pLayout->setSpacing(5);
	m_pLayout->setMargin(5);

	init();
}

CHistogramPaneWidget::~CHistogramPaneWidget()
{
	delete m_pHistogramPainter;
}

void CHistogramPaneWidget::init()
{
	QVector<int> vect = { 5, 5, 5, 5, 5, 5, 5,5, 5, 5, 5,5, 5,5,5,5,5,5, 7, 20, 20, 11, 11, 11, 12 };
	QVector<int> vect2 = { 7, 20, 20, 11, 11, 11, 12 };

	m_pLayout->setColumnMinimumWidth(0, 400);
	m_pLayout->setColumnMinimumWidth(1, 400);
	m_pLayout->setRowMinimumHeight(0, 400);
	//m_pLayout->setRowMinimumHeight(1, 400);
	//pLayout->setRowMinimumHeight(3, 600);

	//pLayout->addWidget(new CHistogram(vect));

	//pLayout->addWidget(new CHistogram(vect));

	//pLayout->addWidget(new CHistogram(vect));

	m_pLayout->addWidget(new CHistogram(vect, m_pHistogramPainter, this));
	m_pLayout->addWidget(new CHistogram(vect2, m_pHistogramPainter, this));
	m_pLayout->addWidget(new CHistogram(vect, m_pHistogramPainter, this));
	m_pLayout->addWidget(new CHistogram(vect, m_pHistogramPainter, this));
}

bool CHistogramPaneWidget::eventFilter(QObject *pObj, QEvent *pEvent)
{
	if (pEvent->type() == QEvent::MouseButtonRelease)
	{
		CHistogram *pHistogram = static_cast<CHistogram*>(pObj);
		
		QSize nScreenSize = qApp->screens()[0]->size();

		m_pHistogramDialogBox->setFixedSize(nScreenSize);
		m_pHistogramDialogBox->showMaximized();
		m_pHistogramDialogBox->setConfig(pHistogram->getConfig());
		m_pHistogramDialogBox->showHistogram();
	}
	else if (pEvent->type() == QEvent::Enter)
		QApplication::setOverrideCursor(Qt::PointingHandCursor);

	else if (pEvent->type() == QEvent::Leave)
		QApplication::restoreOverrideCursor();

	return QWidget::eventFilter(pObj, pEvent);;
}

#include <QScrollBar>
#include <QGridLayout>
#include <QApplication>

// Local includes
#include "Chart.h"
#include "ChartView.h"

////////////////////////////////////////////////////////////////////////////////
//
//	CChartViewPane
//
CChartViewPane::CChartViewPane(QWidget *pParent) : IChartView(pParent)
{
	//setMinimumWidth(800);
	m_pLayout = new QGridLayout(this);
	setLayout(m_pLayout);

	// for setting layout max or min sizes
	m_pLayout->setMargin(5);
	m_pLayout->setSpacing(5);
	m_pLayout->setSizeConstraint(QLayout::SetMinAndMaxSize);
}

CChartViewPane::~CChartViewPane()
{
	for (auto pPainter : m_mapPainter)
		delete pPainter;

	m_mapPainter.clear();
}

void CChartViewPane::addPainter(EChartType eType, IPainter* pPainter)
{
	if (pPainter == nullptr)
		return;

	m_mapPainter.insert(eType, pPainter);
}

IPainter* CChartViewPane::getPainter(EChartType eType) const
{
	return m_mapPainter.value(eType);
}

void CChartViewPane::addChart(IChartData* pChartData)
{
	if (pChartData == nullptr)
		return;

	updateGeometry();
	
	int nChartId = m_mapChartData.count() + 1;
	m_mapChartData.insert(nChartId, pChartData);

	switch (pChartData->eType)
	{
		case EChartType::Histogram:
		{
			CHistogramPainter* pPainter = dynamic_cast<CHistogramPainter*>(m_mapPainter.value(pChartData->eType));
			if (pPainter == nullptr)
				return;

			CHistogram *pHistogram = new CHistogram(dynamic_cast<CHistogramData*>(pChartData), pPainter, this);
			m_pLayout->addWidget(pHistogram);
			
			// set Id to widget
			pHistogram->setObjectName(QString::number(nChartId));

			if (nChartId == 1)
				emit sigChartChecked(pChartData, pPainter);

			break;
		}
	}
}

void CChartViewPane::clear()
{
	while (QLayoutItem* pItem = m_pLayout->takeAt(0))
	{
		Q_ASSERT(!pItem->layout()); // otherwise the layout will leak
		delete pItem->widget();
		delete pItem;
	}
	delete m_pLayout;

	m_pLayout = new QGridLayout(this);
	setLayout(m_pLayout);

	// for setting layout max or min sizes
	m_pLayout->setMargin(5);
	m_pLayout->setSpacing(5);
	m_pLayout->setSizeConstraint(QLayout::SetMinAndMaxSize);

	// clear Chart Data
	for (auto pChartData : m_mapChartData)
		delete pChartData;

	m_mapChartData.clear();
}

void CChartViewPane::updateGeometry()
{
	int nWidth = (m_pLayout->count() == 0) ? width() : (width() / 2);

	m_pLayout->setColumnMinimumWidth(0, nWidth);

	//if (m_pLayout->count() != 0)
	m_pLayout->setColumnMinimumWidth(1, nWidth);

	for (int i = 0; i < m_pLayout->rowCount(); i++)
		m_pLayout->setRowMinimumHeight(i, nWidth);
}

bool CChartViewPane::eventFilter(QObject *pObj, QEvent *pEvent)
{
	IChart *pChart = static_cast<CHistogram*>(pObj);
	if (pChart == nullptr)
		return QWidget::eventFilter(pObj, pEvent);

	int nChartId = pChart->objectName().toInt();
	IChartData* pChartData = m_mapChartData.value(nChartId);
	if (pChartData == nullptr)
		return QWidget::eventFilter(pObj, pEvent);

	while (pEvent->type() == QEvent::MouseButtonPress)
	{		
		QMouseEvent *pMouseEvent = static_cast<QMouseEvent*>(pEvent);
		if (pMouseEvent->buttons() != Qt::LeftButton)
			break;
		
		if (dynamic_cast<CHistogram*>(pChart) != nullptr)
		{
			IPainter* pHistogramPainter = getPainter(EChartType::Histogram);
			if (pHistogramPainter == nullptr)
				break;

			emit sigChartChecked(pChartData, pHistogramPainter);
		}
		break;
	}

	if (pEvent->type() == QEvent::Enter)
	{
		QApplication::setOverrideCursor(Qt::PointingHandCursor);
		pChart->setStyleSheet("border: 3px solid #2980B9;");
	}
	
	if (pEvent->type() == QEvent::Leave)
	{
		QApplication::restoreOverrideCursor();
		pChart->setStyleSheet("border: 2px solid none;");
	}

	return QWidget::eventFilter(pObj, pEvent);
}
////////////////////////////////////////////////////////////////////////////////
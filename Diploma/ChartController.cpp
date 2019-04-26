#include <QFutureSynchronizer>
#include <QtConcurrent/qtconcurrentrun.h>

// Local includes
#include "MainWIndow.h"
#include "ChartPainter.h"
#include "ChartController.h"

////////////////////////////////////////////////////////////////////////////////
//
//	CChartController
//
CChartController::CChartController(CMainWindow* pMaster)
	: m_pMaster(pMaster) {}

CChartController::~CChartController() 
{
	for (auto pModel : m_mapChartModel)
		delete pModel;

	m_mapChartModel.clear();

	delete m_pChartView;
}

void CChartController::run(QVector<double> aNumericValues, QString const& sName, EChartType eType)
{
	IChartData* oChartData = nullptr;

	switch (eType)
	{
		case EChartType::Histogram:
		{
			CHistogramModel* pHistoModel = dynamic_cast<CHistogramModel*>(m_mapChartModel.value(eType));
			if (pHistoModel != nullptr && m_pMaster != nullptr)
			{
				pHistoModel->setBinCount(m_pMaster->getBinCount());
				oChartData = pHistoModel->run(aNumericValues);
			}
			break;
		}
	}

	oChartData->sName = sName;

	if (oChartData != nullptr)
		m_pChartView->addChart(oChartData);
}

void CChartController::clear()
{
	if (m_pChartView != nullptr)
		m_pChartView->clear();
}

void CChartController::setView(IChartView* pView)
{
	m_pChartView = pView;
}

void CChartController::addModel(EChartType eType, IChartModel* pModel)
{
	if (m_pChartView == nullptr)
		return;

	m_mapChartModel.insert(eType, pModel);

	switch (eType)
	{
	case EChartType::Histogram:
		IPainter* pPainter = new CHistogramPainter();
		m_pChartView->addPainter(eType, pPainter);
	}
}

////////////////////////////////////////////////////////////////////////////////
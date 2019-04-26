#ifndef ChartController_H
#define ChartController_H

#include <QMap>
#include <QVector>

// Local includes
#include "ChartView.h"
#include "ChartModel.h"
#include "Definitions.h"

class CMainWindow;

////////////////////////////////////////////////////////////////////////////////
//
//	IChartController
//
class IChartController
{
public:
	virtual void clear() = 0;
	virtual void setView(IChartView* pView) = 0;
	virtual void addModel(EChartType eType, IChartModel* pModel) = 0;
	virtual void run(QVector<double> aData, QString const& sName, EChartType eType) = 0;
};
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
//	CChartController
//
class CChartController : public IChartController
{
public:
	CChartController(CMainWindow *pMaster);
	~CChartController();

public:
	//
	//! IChartController Interface
	//
	void clear() override;
	void setView(IChartView* pView) override;
	void addModel(EChartType eType, IChartModel* pModel) override;
	void run(QVector<double> aData, QString const& sName, EChartType eType) override;

private:
	CMainWindow*		  m_pMaster	   = nullptr;
	IChartView*			  m_pChartView = nullptr;
	QMap<EChartType, IChartModel*> m_mapChartModel;
};
////////////////////////////////////////////////////////////////////////////////

#endif // ChartController_H


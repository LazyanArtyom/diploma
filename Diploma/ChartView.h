#ifndef ChartView_H
#define ChartView_H

#include <QMap>
#include <QWidget>
#include <QGridLayout>

// Local includes
#include "Definitions.h"
#include "ChartPainter.h"

////////////////////////////////////////////////////////////////////////////////
//
//	IChartView
//
class IChartView : public QWidget
{
	Q_OBJECT
public:
	IChartView(QWidget* pParent = nullptr) : QWidget(pParent) {}

	virtual void clear() = 0;
	virtual void addChart(IChartData* oChartData) = 0;
	virtual void addPainter(EChartType eType, IPainter* pPainter) = 0;
	virtual IPainter* getPainter(EChartType eType) const = 0;

signals:
	void sigChartChecked(IChartData* pChartData, IPainter* pPainter);
};
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
//	CChartViewPane
//
class CChartViewPane : public IChartView
{
public:
	CChartViewPane(QWidget *pParent = nullptr);
	~CChartViewPane();

public:
	//
	//! IChartView Interface
	//
	void clear() override;
	void addChart(IChartData* pChartData) override;
	void addPainter(EChartType eType, IPainter* pPainter) override;
	IPainter* getPainter(EChartType eType) const override;

protected:
	void updateGeometry();
	bool eventFilter(QObject *pObj, QEvent *pEvent);

private:
	QGridLayout* m_pLayout			 = nullptr;
	IChartData*	 m_oChartData		 = nullptr;
	IPainter*	 m_pHistogramPainter = nullptr;

	QMap<int, IChartData*> m_mapChartData;
	QMap<EChartType, IPainter*> m_mapPainter;
};
////////////////////////////////////////////////////////////////////////////////

#endif // ChartView_H

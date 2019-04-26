#ifndef ChartReviewPane_H
#define ChartReviewPane_H

#include <QWidget>

// Local includes
#include "Definitions.h"

class IPainter;

////////////////////////////////////////////////////////////////////////////////
//
//	ChartReviewPane
//
class ChartReviewPane : public QWidget
{
	Q_OBJECT
public:
	ChartReviewPane(QWidget *pParent = nullptr);

protected:
	void paintEvent(QPaintEvent *pEvent) override;

private:
	bool		m_bIsChecked = false;
	IPainter*   m_pPainter   = nullptr;
	IChartData* m_pChartData = nullptr;

public slots:
	void onChartChecked(IChartData* pChartData, IPainter* pPainter);
};
////////////////////////////////////////////////////////////////////////////////

#endif // ChartReviewPane_H



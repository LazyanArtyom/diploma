#ifndef HistogramReviewPaneWidget_H
#define HistogramReviewPaneWidget_H

#include <QWidget>
#include "HistogramPainter.h"
#include "HistogramModel.h"

class CHistogram;

class CHistogramReviewPaneWidget final : public QWidget
{
	Q_OBJECT
public:
	CHistogramReviewPaneWidget(QWidget *pParent = 0);
	~CHistogramReviewPaneWidget();

	void updateConfig();

	void setHistogramData(const t_sHistogramData &oHistogramData);
	void setPainter(CHistogramPainter *pHistogramPainter);

protected:
	void paintEvent(QPaintEvent *pEvent) override;

private:
	t_sHistogramConfig m_oCfg;
	t_sHistogramData m_oHistogramData;
	CHistogramPainter *m_pHistogramPainter;
	bool m_bIsChecked;

public slots:
	void onHistogramChecked(t_sHistogramConfig &oCfg);
};

#endif // HistogramReviewPaneWidget_H



#ifndef HistogramDialogBox_H
#define HistogramDialogBox_H

#include <QDialog>
#include "HistogramPainter.h"

class CHistogram;

class CHistogramDialogBox final : public QDialog
{
public:
	CHistogramDialogBox(QWidget *pParent = 0);
	~CHistogramDialogBox();

	void updateConfig();

	void setConfig(t_sHistogramConfig &oCfg);
	void setPainter(CHistogramPainter *pHistogramPainter);
	void showHistogram();

protected:
	void paintEvent(QPaintEvent *pEvent) override;

private:
	t_sHistogramConfig m_oCfg;
	CHistogramPainter *m_pHistogramPainter;
	bool m_bHasConfig;
};

#endif



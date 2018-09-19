#include "HistogramDialogBox.h"
#include "Histogram.h"

CHistogramDialogBox::CHistogramDialogBox(QWidget *pParent)
	: m_pHistogramPainter(nullptr), m_bHasConfig(false), QDialog(pParent)
{
	// for diabling help button 
	setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);
}

CHistogramDialogBox::~CHistogramDialogBox() {}

void CHistogramDialogBox::setConfig(t_sHistogramConfig &oCfg)
{
	m_oCfg = oCfg;
}

void CHistogramDialogBox::setPainter(CHistogramPainter *pHistogramPainter)
{
	m_pHistogramPainter = pHistogramPainter;
}

void CHistogramDialogBox::updateConfig()
{
	m_oCfg.nWidth = this->height() - m_oCfg.nLeftMargin;
	m_oCfg.nHeight = this->height() - (m_oCfg.nBottomMargin + 30);

	m_bHasConfig = true;
}

void CHistogramDialogBox::showHistogram()
{
	updateConfig();
	update();
}

void CHistogramDialogBox::paintEvent(QPaintEvent *pEvent)
{
	if (m_bHasConfig)
	{
		QPainter painter(this);

		// translate histogram to center of screen
		painter.translate((width() - m_oCfg.nWidth) / 2, 0);

		m_pHistogramPainter->draw(&painter, m_oCfg);
	}
}
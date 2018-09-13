#ifndef CPlot_H
#define CPlot_H

#include <QWidget>
#include <QResizeEvent>
#include <QPaintEvent>
#include <QRect>

class CPlot;

class CHistogram final : public QWidget
{
public:
	CHistogram(QVector<int> vectData, QWidget *pParent = 0);
	~CHistogram();

protected:
	void resizeEvent(QResizeEvent *pEvent);

private:
	CPlot *m_pPlot;
	QVector<int> m_vectData;
};

class CPlot final : public QWidget
{
public:
	CPlot(QVector<int> vectData, QWidget *pParent = 0);
	~CPlot();

protected:
	void resizeEvent(QResizeEvent *pEvent);
	void paintEvent(QPaintEvent *pEvent);

private:
	void drawPlot(QPainter *pPainter);
	void drawAxes(QPainter *pPainter);
	void drawBins(QPainter *pPainter);
	void drawHeader(QPainter *pPainter);
	void drawFooter(QPainter *pPainter);

	void clear();
	void run();

private:
	class CRange
	{
	public:
		CRange(int nLow, int nHigh);
		bool inRange(int nValue);

	private:
		int m_nLow;
		int m_nHigh;
	};

	class CBin
	{
	public:
		CBin(int nX1, int nX2);
		~CBin();

		int getHeight();
		QPair<int, int> getWidth();
		
		void increaseHeight(int nVal);

		void setRange(int nLow, int nHigh);
		CRange* getRange();

	private:
		QPair<int, int> m_nBinWidth;
		int m_nBinHeight;
		CRange* m_pRange;
	};

	int m_nWidth;
	int m_nHeight;
	int m_nLeftMargin;
	int m_nRightMargin;
	int m_nTopMargin;
	int m_nBottomMargin;
	int m_nBinsCount;
	int m_nMaxFrequencyCount;
	int m_nBinsWidth;
	int m_nMin;
	int m_nMax;
	int m_nYCordinatesOffset;

	QVector<int> m_vectData;
	QMap<int, int> m_mapFrequency;

	QList<CBin*> m_lstBins;
};

#endif


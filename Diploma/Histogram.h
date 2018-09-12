#ifndef CHistogram_H
#define CHistogram_H

#include <QWidget>
#include <QResizeEvent>
#include <QPaintEvent>
#include <QRect>

class CHistogram : public QWidget
{
public:
	CHistogram(QVector<int> vectData, QWidget *pParent = 0);
	~CHistogram();

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

		QRect getRect();
		int getHeight();
		QPair<int, int> getWidth();
		void setScale(int nScale);
		void increaseHeight(int nVal);
		void setRange(int nLow, int nHigh);
		CRange* getRange();

	private:
		QPair<int, int> m_nBinWidth;
		int m_nBinHeight;
		int m_BinScale;
		CRange* m_pRange;
	};

	int m_nWidht;
	int m_nHeight;
	int m_nBinsCount;
	int m_nMaxFrequencyCount;
	int m_nBinsWidth;
	int m_nMin;
	int m_nMax;

	QVector<int> m_vectData;
	QMap<int, int> m_mapFrequency;

	QList<CBin*> m_lstBins;
};

#endif


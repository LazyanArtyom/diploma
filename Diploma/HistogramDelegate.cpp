#include "HistogramDelegate.h"
#include "Histogram.h"
#include <QPainter>
#include <QApplication>

HistogramDelegate::HistogramDelegate(QObject *pParent) : QStyledItemDelegate(pParent)
{
}


HistogramDelegate::~HistogramDelegate()
{
}

QWidget* HistogramDelegate::createEditor(QWidget *pParent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
	Histogram *pHistogram = new Histogram(pParent);
	pHistogram->setAutoFillBackground(true);

	return pHistogram;
}

void HistogramDelegate::setEditorData(QWidget *pEditor, const QModelIndex &index) const
{
	Histogram *pHistogram = static_cast<Histogram*>(pEditor);
	// settt value tohistogram index.data.toint

}

void HistogramDelegate::setModelData(QWidget *pEditor, QAbstractItemModel *pModel, const QModelIndex &index) const
{
}

void HistogramDelegate::updateEditorGeometry(QWidget *pEditor, const QStyleOptionViewItem & option, const QModelIndex &index) const
{
	pEditor->setGeometry(option.rect);
}

QSize HistogramDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
	QSize result = QStyledItemDelegate::sizeHint(option, index);
	result.setHeight(result.height() * 6);
	return QSize(400, 200);
}

void HistogramDelegate::paint(QPainter *pPainter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
	QString text = "Histogram";
	QRectF r = option.rect;
	pPainter->setPen(Qt::black);
	pPainter->drawRect(r);
	pPainter->setFont(QFont("Times", 36, QFont::Bold));
	pPainter->setPen(QPen(Qt::green, 3, Qt::DashDotLine, Qt::RoundCap, Qt::RoundJoin));
	pPainter->drawText(r, Qt::AlignCenter, text);
}

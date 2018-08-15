#ifndef HISTOGRAMDELEGATE_H
#define HISTOGRAMDELEGATE_H

#include <QStyledItemDelegate>

class HistogramDelegate : public QStyledItemDelegate
{
public:
	HistogramDelegate(QObject *pParent = 0);
	~HistogramDelegate();

	QWidget* createEditor(QWidget *pParent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
	void setEditorData(QWidget *pEditor, const QModelIndex &index) const override;
	void setModelData(QWidget *pEditor, QAbstractItemModel *pModel, const QModelIndex &index) const override;
	void updateEditorGeometry(QWidget *pEditor, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
	QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;
	void paint(QPainter *pPainter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};

#endif // HISTOGRAMDELEGATE_H

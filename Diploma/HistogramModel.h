#ifndef HISTOGRAMMODEL_H
#define HISTOGRAMMODEL_H

#include <QAbstractTableModel>

class HistogramModel : public QAbstractTableModel
{
	Q_OBJECT
public:
	HistogramModel(QObject *parent = 0);
	~HistogramModel();

	// Inherited via QAbstractTableModel
	virtual int rowCount(const QModelIndex & parent = QModelIndex()) const override;

	virtual int columnCount(const QModelIndex & parent = QModelIndex()) const override;

	virtual QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const override;

	//QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

};

#endif // HISTOGRAMMODEL_H

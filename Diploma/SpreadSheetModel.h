#ifndef SPREADSHEETMODEL_H
#define SPREADSHEETMODEL_H

#include <QAbstractTableModel>

class SpreadSheetModel : public QAbstractTableModel
{
	Q_OBJECT
public:
	SpreadSheetModel(QObject *parent = 0);
	~SpreadSheetModel();
	
	// Inherited via QAbstractTableModel
	virtual int rowCount(const QModelIndex & parent = QModelIndex()) const override;

	virtual int columnCount(const QModelIndex & parent = QModelIndex()) const override;

	virtual QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const override;

	QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

};

#endif // SPREADSHEETMODEL_H

#ifndef SpreadSheetPaneWidget_H
#define SpreadSheetPaneWidget_H

#include <QTableView>
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
	QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
	virtual QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const override;
};

class SpreadSheetPaneWidget : public QTableView
{
	Q_OBJECT
public:
	SpreadSheetPaneWidget(QWidget *parent = nullptr);
	~SpreadSheetPaneWidget() = default;

private:
	SpreadSheetModel *m_pModel = nullptr;
};

#endif // SpreadSheetPaneWidget_H

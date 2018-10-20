#ifndef ColSelectorWidget_H
#define ColSelectorWidget_H

#include <QListView>
#include <QStringListModel>
#include <QStringList>
#include <QPersistentModelIndex>
#include <QStyledItemDelegate>
#include <QSet>
#include <QSortFilterProxyModel>

class ColSelectorModel : public QStringListModel
{
	Q_OBJECT
public:
	ColSelectorModel(QObject *parent = 0);
	~ColSelectorModel();

	void addCols(const QStringList lstColNames);

protected:
	// Inherited via QAbstractListModel.o
	virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override;
	virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
	virtual Qt::ItemFlags flags(const QModelIndex &index) const override;
	virtual bool setData(const QModelIndex &index, const QVariant &value, int role) override;

private:
	QStringList m_lstColnames;
	QSet<QPersistentModelIndex> m_lstCheckedItems;
};

class ColSelectorWidget : public QListView
{
	Q_OBJECT
public:
	ColSelectorWidget(QWidget *parent = 0);
	~ColSelectorWidget();

	void AddColumns(QStringList lstColumns);

signals:
	void onColumnsAdded(QStringList lstColumns);

private:
	ColSelectorModel *m_pColSelectorModel;
	QSortFilterProxyModel *proxyModel;

public slots:
	//void onFilterChanged(QString& text);
};

#endif // ColSelectorWidget_H

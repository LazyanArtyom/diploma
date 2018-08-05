#include "ColSelectorModel.h"
#include <QColor>
#include <QSize>

ColSelectorModel::ColSelectorModel(QObject *parent)
	: QStringListModel(parent)
{
	m_lstColnames << "Hello1" << "Hello2" << "Hello3" << "Hello4" << "Hello5";
	setStringList(m_lstColnames);
}

ColSelectorModel::~ColSelectorModel()
{
}

void ColSelectorModel::addCols(QStringList lstColNames)
{
	m_lstColnames = lstColNames;
}

int ColSelectorModel::rowCount(const QModelIndex & parent) const
{
	return m_lstColnames.count();
}

QVariant ColSelectorModel::data(const QModelIndex & index, int role) const
{
	if (!index.isValid())
		return QVariant();

	switch (role)
	{
	case Qt::DisplayRole:
		return m_lstColnames.at(index.row());
	
	case Qt::CheckStateRole:
		return m_lstCheckedItems.contains(index) ? Qt::Checked : Qt::Unchecked;

	case Qt::BackgroundColorRole:
		return m_lstCheckedItems.contains(index) ? QColor("#ffffb2") : QColor("#ffffff");

	case Qt::SizeHintRole:
		return QSize(0, 30);
	}

	return QStringListModel::data(index, role);
}

Qt::ItemFlags ColSelectorModel::flags(const QModelIndex &index) const
{
	Qt::ItemFlags defaultFlags = QStringListModel::flags(index);

	if (index.isValid())
		return defaultFlags | Qt::ItemIsUserCheckable;

	return defaultFlags;
}

bool ColSelectorModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
	if (!index.isValid() || role != Qt::CheckStateRole)
		return false;

	if (value == Qt::Checked)
		m_lstCheckedItems.insert(index);
	else
		m_lstCheckedItems.remove(index);

	if (role == Qt::EditRole)
		return false;

	//emit dataChanged(index, index);
	return true;
}

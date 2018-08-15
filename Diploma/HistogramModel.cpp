#include "HistogramModel.h"
#include <QColor>
#include <QBrush>

HistogramModel::HistogramModel(QObject *parent)
	: QAbstractTableModel(parent)
{
}

HistogramModel::~HistogramModel()
{
}

int HistogramModel::rowCount(const QModelIndex &parent) const
{
	return 5;
}

int HistogramModel::columnCount(const QModelIndex &parent) const
{
	return 2;
}

QVariant HistogramModel::data(const QModelIndex &index, int role) const
{
	if (!index.isValid())
		return QVariant();

	switch (role)
	{
	case Qt::DisplayRole:
		return QString("Row%1, Column%2")
			.arg(index.row() + 1)
			.arg(index.column() + 1);

	default:
		return QVariant();
	}

	return QVariant();
}
/*
QVariant HistogramModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (orientation == Qt::Horizontal)
	{
		if (role == Qt::DisplayRole)
		{
			if (section == 0)
				return QString("first");

			if (section == 1)
				return QString("second");

			if (section == 2)
				return QString("third");
		}
	}

	return QAbstractTableModel::headerData(section, orientation, role);
}
*/
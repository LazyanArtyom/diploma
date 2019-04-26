#include "SpreadSheetPaneWidget.h"
#include <QHeaderView>
#include <QColor>
#include <QBrush>

/* Model Implementations */
SpreadSheetModel::SpreadSheetModel(QObject *parent)
	: QAbstractTableModel(parent)
{
}

SpreadSheetModel::~SpreadSheetModel()
{
}

int SpreadSheetModel::rowCount(const QModelIndex &parent) const
{
	return 21;
}

int SpreadSheetModel::columnCount(const QModelIndex &parent) const
{
	return 11;
}

QVariant SpreadSheetModel::data(const QModelIndex &index, int role) const
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

QVariant SpreadSheetModel::headerData(int section, Qt::Orientation orientation, int role) const
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

/* View Implementations */
SpreadSheetPaneWidget::SpreadSheetPaneWidget(QWidget *parent) : QTableView(parent)
{
	m_pModel = new SpreadSheetModel();
	setModel(m_pModel);

	verticalHeader()->hide();
	horizontalHeader()->setStyleSheet("QHeaderView::section { background-color: #BDC3C7; padding: 10px; }");
}